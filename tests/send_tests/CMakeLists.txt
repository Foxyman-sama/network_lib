cmake_minimum_required(VERSION 3.28)
project(send_tests)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} send_tests.cxx)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} 
    GTest::gtest_main 
    GTest::gmock_main
)

add_test(${PROJECT_NAME} ${PROJECT_NAME})