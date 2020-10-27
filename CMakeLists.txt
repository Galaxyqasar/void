cmake_minimum_required(VERSION 3.17)
project(void)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(voidcore)
add_subdirectory(src)
target_include_directories(voidcore PUBLIC include)
add_executable(void src/void.cpp)
target_include_directories(void PUBLIC include)
target_link_libraries(void voidcore)

enable_testing()
add_subdirectory(tests)