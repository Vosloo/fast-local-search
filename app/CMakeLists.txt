cmake_minimum_required(VERSION 3.13)

project(app)

add_executable(main main.cpp)

target_link_libraries(main
    PRIVATE source)

target_compile_features(main PUBLIC cxx_std_20)
