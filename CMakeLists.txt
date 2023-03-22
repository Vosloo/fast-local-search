# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.13)

project(
    Project_1
    VERSION 0.1
    DESCRIPTION "Project no. 1 for bio_evo")

add_subdirectory(source)
add_subdirectory(app)
