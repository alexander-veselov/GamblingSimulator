cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME RoflCasino)
set(TESTS_NAME ${PROJECT_NAME}Tests)
set(SOURCES_DIR ${CMAKE_SOURCE_DIR}/source)
set(THIRD_PARTY_PATH ${CMAKE_SOURCE_DIR}/third-party)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

project(${PROJECT_NAME})

enable_testing()

add_executable(${PROJECT_NAME} source/main.cpp)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

include_directories(${SOURCES_DIR})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Emscripten already has includes.
# But we need it to path consistency (e.g. SDL2/SDL2.h vs SDL2.h)
include_directories(
	${THIRD_PARTY_PATH}/SDL2/include
	${THIRD_PARTY_PATH}/SDL2_ttf/include
)

add_subdirectory(${THIRD_PARTY_PATH})
add_subdirectory(${SOURCES_DIR}/Core)
add_subdirectory(${SOURCES_DIR}/Application)
add_subdirectory(${SOURCES_DIR}/UnitTests)

target_link_libraries(${PROJECT_NAME} ApplicationLib CoreLib)

if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	set(FLAGS -sUSE_SDL=2
	          -sUSE_SDL_TTF=2
			  -sINITIAL_MEMORY=2GB
			  --bind
			  --emrun
			  --shell-file ${SOURCES_DIR}/Index.html
			  --preload-file resources/font.ttf)
	string(REPLACE ";" " " FLAGS_STR "${FLAGS}")

	set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .html)
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS ${FLAGS_STR})
endif()

file(INSTALL resources DESTINATION .)