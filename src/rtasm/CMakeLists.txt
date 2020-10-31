target_include_directories(voidcore PRIVATE ${CMAKE_SOURCE_DIR}/include/rtasm)
target_sources(voidcore PRIVATE program.cpp)
target_sources(voidcore PRIVATE rtasm.cpp)