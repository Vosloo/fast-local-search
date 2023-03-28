cmake_minimum_required(VERSION 3.13)

project(app)

set(APP_SOURCES
    include/DistanceMatrix.hpp
    include/FileReader.hpp
    include/Instance.hpp
    include/Node.hpp
    include/Solution.hpp
    include/utils.hpp
    include/algorithms/AbstractAlgorithm.hpp
    include/algorithms/GreedyAlgorithm.hpp
    include/algorithms/HeuristicAlgorithm.hpp
    include/algorithms/RandomAlgorithm.hpp
    include/algorithms/RandomWalkAlgorithm.hpp
    include/algorithms/SteepestAlgorithm.hpp
    src/DistanceMatrix.cpp
    src/FileReader.cpp
    src/Instance.cpp
    src/Node.cpp
    src/Solution.cpp
    src/utils.cpp
    src/algorithms/GreedyAlgorithm.cpp
    src/algorithms/HeuristicAlgorithm.cpp
    src/algorithms/RandomAlgorithm.cpp
    src/algorithms/RandomWalkAlgorithm.cpp
    src/algorithms/SteepestAlgorithm.cpp
)

add_library(app_lib ${APP_SOURCES})

target_include_directories(app_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(main main.cpp)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(main app_lib)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)
target_compile_features(app_lib PUBLIC cxx_std_20)
target_compile_features(main PUBLIC cxx_std_20)
