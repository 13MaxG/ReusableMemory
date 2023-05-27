cmake_minimum_required(VERSION 3.26.2)
project(Reusable)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(DCMAKE_MACOSX_RPATH ON)

find_package (Eigen3 3.3 REQUIRED)
find_package(GTest REQUIRED)
message(Hi -${GTEST_ROOT})

enable_testing()
add_executable(Tests ReusableMatrixTest.cpp)
target_link_libraries(Tests GTest::gtest GTest::gtest_main)
target_link_libraries(Tests Eigen3::Eigen)
gtest_discover_tests(Tests)