set(ROCPROFILER_LIB_VULKAN_SOURCES layer.cpp vulkan.cpp)
set(ROCPROFILER_LIB_VULKAN_HEADERS defines.hpp layer.hpp utils.hpp vulkan_dispatch.hpp
                                   vulkan.hpp)

target_sources(rocprofiler-sdk-object-library PRIVATE ${ROCPROFILER_LIB_VULKAN_SOURCES}
                                                      ${ROCPROFILER_LIB_VULKAN_HEADERS})

# add_subdirectory(details)
