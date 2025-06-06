add_executable(arl_cli)

target_link_libraries(arl_cli
PUBLIC
    arl_api
)

file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

target_include_directories(arl_cli
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(arl_cli
PRIVATE
    ${headers}
    ${sources}
)