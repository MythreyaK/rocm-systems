# Vulkan Loader ↔ Layer Negotiation — Full Sequence

A full Vulkan-specific sequence of the loader↔layer lifecycle: discovery, per-layer version negotiation (interface v2), chain assembly, instance/device create chaining, and steady-state dispatch. Two layers are shown so the chaining is visible.

```mermaid
sequenceDiagram
    autonumber
    participant App as Application
    participant Ld as Loader (libvulkan.so.1)
    participant L0 as Layer 0 (top, nearest app)
    participant L1 as Layer 1 (bottom, nearest ICD)
    participant ICD as ICD / Driver

    Note over App,Ld: Process start — DT_NEEDED on libvulkan.so.1<br/>vkCreateInstance / vkGetInstanceProcAddr resolve to LOADER trampolines

    App->>Ld: vkCreateInstance(pCreateInfo, &instance)

    rect rgba(96,165,250,0.15)
    Note over Ld: PHASE 1 — Discovery (metadata only)
    Ld->>Ld: loader_scan_for_layers()<br/>read JSON manifests in explicit_layer.d / implicit_layer.d (+ VK_LAYER_PATH)
    Ld->>L0: dlopen(library_path)  [enabled layers only]
    Ld->>L1: dlopen(library_path)
    end

    rect rgba(74,222,128,0.15)
    Note over Ld,L1: PHASE 2 — Version negotiation (per layer, BEFORE any GetProcAddr)
    Ld->>L0: vkNegotiateLoaderLayerInterfaceVersion(&s)<br/>s.loaderLayerInterfaceVersion = 2
    L0-->>Ld: s.pfnGetInstanceProcAddr = L0_gipa<br/>s.pfnGetDeviceProcAddr = L0_gdpa
    Ld->>L1: vkNegotiateLoaderLayerInterfaceVersion(&s)
    L1-->>Ld: s.pfnGetInstanceProcAddr = L1_gipa<br/>s.pfnGetDeviceProcAddr = L1_gdpa
    end

    rect rgba(251,191,36,0.15)
    Note over Ld: PHASE 3 — Build the chain (link-info linked list)
    Ld->>Ld: create VkLayerInstanceLink nodes<br/>L0.pfnNextGetInstanceProcAddr = L1_gipa<br/>L1.pfnNextGetInstanceProcAddr = loader-terminator gipa (→ ICD)
    Ld->>Ld: thread VkLayerInstanceCreateInfo (function=VK_LAYER_LINK_INFO)<br/>into pCreateInfo->pNext
    end

    rect rgba(244,114,182,0.15)
    Note over Ld,ICD: PHASE 4 — CreateInstance flows DOWN the chain (each layer consumes + advances)
    Ld->>L0: L0_gipa(NULL,"vkCreateInstance") → L0::CreateInstance(pCreateInfo)
    L0->>L0: read pLayerInfo->pfnNextGetInstanceProcAddr (= L1_gipa)<br/>advance: pLayerInfo = pLayerInfo->pNext
    L0->>L1: next_gipa(NULL,"vkCreateInstance") → L1::CreateInstance
    L1->>L1: read next (= loader terminator)<br/>advance pLayerInfo
    L1->>ICD: loader terminator → vkCreateInstance (real)
    ICD-->>L1: VkInstance
    L1->>L1: loader_set_dispatch(instance)<br/>cache onward gipa in private table
    L1-->>L0: VK_SUCCESS
    L0->>L0: loader_set_dispatch wrapping<br/>cache onward gipa
    L0-->>Ld: VK_SUCCESS
    Ld-->>App: VkInstance (dispatch table ptr in first machine word)
    end

    rect rgba(96,165,250,0.15)
    Note over App,ICD: PHASE 5 — Device creation (analogous, device chain)
    App->>L0: vkCreateDevice(physDev, pCreateInfo) via instance dispatch
    Note over Ld,L1: VkLayerDeviceCreateInfo carries pfnNextGetDeviceProcAddr (gdpa chain)
    L0->>L1: consume + advance device link, call down
    L1->>ICD: terminator → real vkCreateDevice
    ICD-->>App: VkDevice (dispatch ptr in first word)
    end

    rect rgba(74,222,128,0.15)
    Note over App,ICD: PHASE 6 — Steady state (per call: 1 load + 1 indirect call)
    App->>L0: vkQueueSubmit(queue,...)  [via queue's dispatch table ptr]
    L0->>L0: intercept work (record / wrap)
    L0->>L1: forward via cached next pointer
    L1->>ICD: forward
    ICD-->>App: result
    end
```

## Details encoded above that are easy to miss

- **Negotiate happens before any `GetProcAddr`.** At interface v2 the loader takes `pfnGetInstanceProcAddr` / `pfnGetDeviceProcAddr` *out of the negotiate struct itself*; the legacy (<2) path would `dlsym` them separately.
- **The loader builds the order.** Layers do not discover their neighbors. Each layer only *consumes* its `pfnNextGetInstanceProcAddr` and *advances* `pLayerInfo = pLayerInfo->pNext` so the layer below gets its own node.
- **Instance and device chains are separate.** `gipa` flows via `VkLayerInstanceCreateInfo` / `VK_LAYER_LINK_INFO`; `gdpa` flows via `VkLayerDeviceCreateInfo`.
- **The bottom of each chain is the loader's terminator**, which dispatches into the ICD.
- **Steady-state dispatch** uses the table pointer stored in the dispatchable object's first machine word — set via `loader_set_dispatch`.
