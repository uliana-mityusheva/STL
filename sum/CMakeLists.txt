cmake_minimum_required(VERSION 3.0)
project(sum)
 
set(CMAKE_CXX_STANDARD 17)
 
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)
 
set(SUM_SRC ${CMAKE_SOURCE_DIR}/sum.cpp)
 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror -Wno-self-assign-overloaded -Wno-missing-braces")
 
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
#link_libraries(gtest gtest_main pthread)
 
add_executable(sum_public_test ${SUM_SRC} sum_public_test.cpp)
target_link_libraries(sum_public_test Threads::Threads ${GTEST_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})
include_directories(${CMAKE_SOURCE_DIR}/../../sum)
 
install (
        TARGETS sum_public_test
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
)