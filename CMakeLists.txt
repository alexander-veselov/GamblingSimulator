cmake_minimum_required(VERSION 3.10)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(PROJECT_NAME RoflCasino)
project(${PROJECT_NAME})

# Get source files
file(GLOB ALL_SOURCES
     "source/*.h"
     "source/*.cpp"
	 "source/Application/*.h"
     "source/Application/*.cpp"
	 "source/Core/*.h"
     "source/Core/*.cpp"
)
if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	file(GLOB PLATFORM_SOURCES
		"source/Application/WebAssembly/*.h"
		"source/Application/WebAssembly/*.cpp"
	)
	set(THIRD_PARTY_INCLUDES "")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	file(GLOB PLATFORM_SOURCES
		"source/Application/Windows/*.h"
		"source/Application/Windows/*.cpp"
	)
endif()
list (APPEND ALL_SOURCES ${PLATFORM_SOURCES})

# Create executable
add_executable(${PROJECT_NAME} ${ALL_SOURCES})

set(THIRD_PARTY_PATH ${CMAKE_SOURCE_DIR}/third-party)

set(SDL2_VERSION 2.0.18)
set(SDL2_LIBS_PATH ${THIRD_PARTY_PATH}/SDL2-${SDL2_VERSION}/lib/x64)
set(SDL2_TTF_LIBS_PATH ${THIRD_PARTY_PATH}/SDL2_ttf-${SDL2_VERSION}/lib/x64)

find_library(SDL2_LIBS
	NAMES SDL2 SDL2_LIBS_PATH
	PATHS ${SDL2_LIBS_PATH}
)
find_library(SDL2_TTF_LIBS 
	NAMES SDL2_ttf
	PATHS ${SDL2_TTF_LIBS_PATH}
)
	
target_include_directories(${PROJECT_NAME}
	PRIVATE
		"${THIRD_PARTY_PATH}/SDL2-${SDL2_VERSION}/include"
		"${THIRD_PARTY_PATH}/SDL2_ttf-${SDL2_VERSION}/include"
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	target_link_libraries(${PROJECT_NAME}
		${SDL2_LIBS}
		${SDL2_TTF_LIBS}
	)

	file(GLOB SDL2_DLLS ${SDL2_LIBS_PATH}/*.dll)
	file(GLOB SDL2_TTF_DLLS ${SDL2_TTF_LIBS_PATH}/*.dll)
	foreach(SDL2_DLL ${SDL2_DLLS})
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD     
			COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_DLL} ${CMAKE_BINARY_DIR})
	endforeach()
	foreach(SDL2_TTF_DLL ${SDL2_TTF_DLLS})
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD     
			COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_TTF_DLL} ${CMAKE_BINARY_DIR})
	endforeach()
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .html)
	set(FLAGS -sUSE_SDL=2
	          -sUSE_SDL_TTF=2
			  -sINITIAL_MEMORY=2GB
			  --bind
			  --emrun
			  --shell-file "${CMAKE_SOURCE_DIR}/source/Index.html"
			  --preload-file "resources/font.ttf")
	string(REPLACE ";" " " FLAGS_STR "${FLAGS}")
	set_target_properties(${PROJECT_NAME}
		PROPERTIES LINK_FLAGS ${FLAGS_STR}
	)
endif()

file(INSTALL resources DESTINATION .)