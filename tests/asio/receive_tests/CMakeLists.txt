cmake_minimum_required(VERSION 3.29)
project(receive_tests)

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} receive_tests.cxx)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} 
    GTest::gtest_main 
    GTest::gmock_main
    network_lib
)

add_test(${PROJECT_NAME} ${PROJECT_NAME})