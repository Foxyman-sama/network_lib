cmake_minimum_required(VERSION 3.29)
project("network_lib")

set(TESTS_ENABLED FALSE)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 26)

find_package(Boost REQUIRED CONFIG)

add_library(${PROJECT_NAME} 
    src/network_impl/asio/asio_tcp_socket.cxx
    src/network_impl/asio/asio_tcp_server.cxx
)

target_include_directories(${PROJECT_NAME} PUBLIC 
    src
    ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES})

if (TESTS_ENABLED)
    enable_testing()
    add_subdirectory(tests)
endif()
