cmake_minimum_required(VERSION 3.10)
project(roscpp_lite)

# general build options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# XMLRPC for ROS Communication
find_package(xmlrpcpp REQUIRED)

# source files
set(SRC_FILES
  src/client_wrapper.cpp
  src/subscriber.cpp
)

# core roscpp_lite library
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} ${xmlrpcpp_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wpedantic)

# include tests
add_subdirectory(test)