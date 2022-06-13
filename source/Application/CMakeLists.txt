cmake_minimum_required(VERSION 3.22)

file(GLOB APPLICATION_SOURCES "*.h" "*.cpp")
add_library(ApplicationLib STATIC ${APPLICATION_SOURCES})
target_link_libraries(ApplicationLib CoreLib ${SDL2_LIBS} ${SDL2_TTF_LIBS})