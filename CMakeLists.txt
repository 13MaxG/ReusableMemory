cmake_minimum_required(VERSION 3.26.2)
project(Reusable)

find_package (Eigen3 3.3 REQUIRED)

add_executable(Reusable main.cpp)
target_compile_features(Reusable PRIVATE cxx_std_17)

target_link_libraries(Reusable Eigen3::Eigen)
