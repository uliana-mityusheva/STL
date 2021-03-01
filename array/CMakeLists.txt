cmake_minimum_required(VERSION 3.0)
project(array)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

set(RATIONAL_SRC ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror -Wno-self-assign-overloaded -Wno-missing-braces")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
#link_libraries(gtest gtest_main pthread)

add_executable(array_public_test array_public_test.cpp) #cmake-build-debug/array.h

include_directories(${CMAKE_SOURCE_DIR}/../../array ${CMAKE_SOURCE_DIR}/..)

target_link_libraries(array_public_test Threads::Threads ${GTEST_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

#install (
#        TARGETS array_public_test
#        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
#)