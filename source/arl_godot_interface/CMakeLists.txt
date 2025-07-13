add_library(arl_godot_interface SHARED)

target_link_libraries(arl_godot_interface
PUBLIC
    godot::cpp
    arl_api
)

file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

target_include_directories(arl_godot_interface
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(arl_godot_interface
PRIVATE
    ${headers}
    ${sources}
)