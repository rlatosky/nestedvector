

cmake_minimum_required(VERSION 3.9)
project(nestedvector_experiments VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -O0 -g -Wall -Wextra -fno-omit-frame-pointer")
if(NOT "${CMAKE_BUILD_TYPE}")
    set(CMAKE_BUILD_TYPE Debug)
endif()


set(NESTEDVECTOR_TESTS_SOURCES
        src/NestedVectorEasy.cpp
        src/NestedVectorMedium.cpp
        src/NestedVectorHard.cpp
        test/NestedVectorTests.cpp
        )

add_executable("nestedvector_tests" ${NESTEDVECTOR_TESTS_SOURCES})
target_include_directories(nestedvector_tests PRIVATE include external)

# target_link_libraries(nestedvector_tests phasm-surrogate)
# install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include/phasm)
