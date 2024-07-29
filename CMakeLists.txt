cmake_minimum_required(VERSION 3.27)
project("network_lib")

add_library(${PROJECT_NAME} main.cxx)

add_subdirectory(tests)