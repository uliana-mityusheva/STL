cmake_minimum_required(VERSION 3.0)
project(rational)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

set(RATIONAL_SRC ${CMAKE_SOURCE_DIR}/rational.cpp) #/../../Mityushyova/rational/rational.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror -Wno-self-assign-overloaded -Wno-missing-braces")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
#link_libraries(gtest gtest_main pthread)

add_executable(rational_public_test ${RATIONAL_SRC} rational_public_test.cpp)

include_directories(${CMAKE_SOURCE_DIR}/../../rational ${CMAKE_SOURCE_DIR}/..)

target_link_libraries(rational_public_test Threads::Threads ${GTEST_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

#install (
#		TARGETS rational_public_test
#		RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
#)
