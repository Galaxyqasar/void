target_include_directories(voidcore PRIVATE ${CMAKE_SOURCE_DIR}/include/stdlib)

file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
foreach(child ${children})
	if(${child} MATCHES ".+\.cpp")
		target_sources(voidcore PRIVATE ${child})
	endif()
endforeach()