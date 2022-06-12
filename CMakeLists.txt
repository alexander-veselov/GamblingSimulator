cmake_minimum_required(VERSION 3.10)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(PROJECT_NAME RoflCasino)
set(TESTS_NAME ${PROJECT_NAME}Tests)
project(${PROJECT_NAME})

# Get source files
file(GLOB ALL_SOURCES
     "source/main.cpp"
	 "source/Application/*.h"
     "source/Application/*.cpp"
	 "source/Core/*.h"
     "source/Core/*.cpp"
)

file(GLOB TESTS_SOURCES
	"source/gtestmain.cpp"
	"source/UnitTests/*.h"
    "source/UnitTests/*.cpp"
	"source/Core/*.h"
    "source/Core/*.cpp"
)

if(MSVC)
  set(variables 
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_RELEASE
	CMAKE_CXX_FLAGS_RELWITHDEBINFO
	CMAKE_CXX_FLAGS_MINSIZEREL
  )
  foreach(variable ${variables})
	if(${variable} MATCHES "/MD")
	  string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
	endif()
  endforeach()
endif()

add_subdirectory(third-party/GoogleTest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Create executable
add_executable(${PROJECT_NAME} ${ALL_SOURCES})
add_executable(${TESTS_NAME} ${TESTS_SOURCES})

target_link_libraries(${TESTS_NAME} gtest gtest_main)
if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	add_test(
	  NAME ${TESTS_NAME}
	  COMMAND node "${CMAKE_CURRENT_BINARY_DIR}/${TESTS_NAME}.js"
	)
else()
	add_test(
	  NAME ${TESTS_NAME}
	  COMMAND $<TARGET_FILE:${TESTS_NAME}>
	)
endif()

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
	
include_directories(
	PRIVATE
		"${CMAKE_SOURCE_DIR}/source"
		"${THIRD_PARTY_PATH}/SDL2-${SDL2_VERSION}/include"
		"${THIRD_PARTY_PATH}/SDL2_ttf-${SDL2_VERSION}/include"
)

if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
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
	set(FLAGS -sUSE_SDL=2
	          -sUSE_SDL_TTF=2
			  -sINITIAL_MEMORY=2GB
			  --bind
			  --emrun
			  --shell-file "${CMAKE_SOURCE_DIR}/source/Index.html"
			  --preload-file "resources/font.ttf")
	string(REPLACE ";" " " FLAGS_STR "${FLAGS}")

	set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .html)
	set_target_properties(${TESTS_NAME} PROPERTIES SUFFIX .html)
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS ${FLAGS_STR})
endif()

file(INSTALL resources DESTINATION .)