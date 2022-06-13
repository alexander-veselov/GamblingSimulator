cmake_minimum_required(VERSION 3.22)

file(GLOB CORE_SOURCES "*.h" "*.cpp")
add_library(CoreLib STATIC ${CORE_SOURCES})