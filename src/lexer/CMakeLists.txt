target_include_directories(voidcore PRIVATE ${CMAKE_SOURCE_DIR}/include/lexer)
target_sources(voidcore PRIVATE error.cpp)
target_sources(voidcore PRIVATE lexer.cpp)
target_sources(voidcore PRIVATE utils.cpp)