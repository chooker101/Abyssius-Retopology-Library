cmake_minimum_required(VERSION 3.16)
project(ARL CXX C)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

add_subdirectory(source)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)