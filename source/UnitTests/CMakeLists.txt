cmake_minimum_required(VERSION 3.22)

file(GLOB TESTS_SOURCES
	"gtestmain.cpp"
	"*.h"
    "*.cpp"
)

add_executable(${TESTS_NAME} ${TESTS_SOURCES})
target_compile_features(${TESTS_NAME} PUBLIC cxx_std_17)

target_link_libraries(${TESTS_NAME} gtest gtest_main CoreLib)

if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	set_target_properties(${TESTS_NAME} PROPERTIES SUFFIX .html)
	set(TESTS_RUN_COMMAND node "${CMAKE_CURRENT_BINARY_DIR}/${TESTS_NAME}.js")
else()
	set(TESTS_RUN_COMMAND $<TARGET_FILE:${TESTS_NAME}>)
endif()

add_test(NAME ${TESTS_NAME} COMMAND ${TESTS_RUN_COMMAND})