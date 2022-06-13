cmake_minimum_required(VERSION 3.22)

# Needed to build GTest using VS compiler
if(MSVC)
  set(VARIABLES 
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_RELEASE
	CMAKE_CXX_FLAGS_RELWITHDEBINFO
	CMAKE_CXX_FLAGS_MINSIZEREL
  )
  foreach(VARIABLE ${variables})
	if(${variable} MATCHES "/MD")
	  string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
	endif()
  endforeach()
endif()

add_subdirectory(${THIRD_PARTY_PATH}/GoogleTest)

# SDL2 Windows x64 library
if(WIN32)
	set(SDL2_LIBS_PATH ${THIRD_PARTY_PATH}/SDL2/lib/x64)
	set(SDL2_TTF_LIBS_PATH ${THIRD_PARTY_PATH}/SDL2_ttf/lib/x64)

	find_library(SDL2_LIBS
		NAMES SDL2 SDL2_LIBS_PATH
		PATHS ${SDL2_LIBS_PATH}
	)
	find_library(SDL2_TTF_LIBS 
		NAMES SDL2_ttf
		PATHS ${SDL2_TTF_LIBS_PATH}
	)

	target_link_libraries(${PROJECT_NAME}
		${SDL2_LIBS}
		${SDL2_TTF_LIBS}
	)

	# Copy dlls to out folder
	file(GLOB SDL2_DLLS ${SDL2_LIBS_PATH}/*.dll)
	file(GLOB SDL2_TTF_DLLS ${SDL2_TTF_LIBS_PATH}/*.dll)
	list(APPEND SDL2_DLLS ${SDL2_TTF_DLLS})
	foreach(SDL2_DLL ${SDL2_DLLS})
		add_custom_command(
			OUTPUT ${CMAKE_BINARY_DIR}/${SDL2_DLL}
			COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_DLL} ${CMAKE_BINARY_DIR}
			DEPENDS ${PROJECT_NAME}
		)
		get_filename_component(LIB_NAME ${SDL2_DLL} NAME)
		add_custom_target(COPY_${LIB_NAME} ALL
			DEPENDS ${CMAKE_BINARY_DIR}/${SDL2_DLL}
		)
	endforeach()
endif()