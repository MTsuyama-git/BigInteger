project(bigInteger)

cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -D__DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_library(bigInteger src/BigInteger.cpp)
add_executable(testBigInteger test/test_BigInteger.cpp)
target_link_libraries(testBigInteger PUBLIC bigInteger)
