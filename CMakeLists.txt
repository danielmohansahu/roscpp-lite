cmake_minimum_required(VERSION 3.10)
project(roscpp_lite)

# general build options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find XMLRPC-C
find_package(XMLRPC REQUIRED COMPONENTS c++2)

# source files
set(SRC_FILES
  src/client_wrapper.cpp
  src/master_client.cpp
  src/server_wrapper.cpp
  src/subscriber.cpp
  src/utils.cpp
)

# core roscpp_lite library
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include ${XMLRPC_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${XMLRPC_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wpedantic)

# compile example file
add_executable(subscriber_example example/subscriber_example.cpp)
target_link_libraries(subscriber_example ${PROJECT_NAME})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wpedantic)

# include tests
# add_subdirectory(test)
