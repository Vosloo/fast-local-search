# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.13)

project(source)

AUX_SOURCE_DIRECTORY(src DIR_SRCS)
message(STATUS "DIR_SRCS = ${DIR_SRCS}")
add_library(source ${DIR_SRCS})

# PUBLIC needed to make library available elsewhere in project
target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Tell compiler to use C++20 features.
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)