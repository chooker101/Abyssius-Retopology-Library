add_library(arl_api STATIC)

file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

target_include_directories(arl_api
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(arl_api
PRIVATE
    ${headers}
    ${sources}
)