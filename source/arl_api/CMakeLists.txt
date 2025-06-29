add_library(arl_api STATIC)

target_link_libraries(arl_api
PUBLIC
    assimp
)

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