target_include_directories(voidcore PRIVATE ${CMAKE_SOURCE_DIR}/include/asm)

target_sources(voidcore PRIVATE assembler.cpp)

if(UNIX)
	target_sources(voidcore PRIVATE program_unix.cpp)
elseif(MSVC)
	target_sources(voidcore PRIVATE program_msvc.cpp)
endif()

add_subdirectory(ins)