cmake -S . -B out/x64-debug -DCMAKE_BUILD_TYPE=DEBUG -G "Ninja"
cmake -S . -B out/x64-release -DCMAKE_BUILD_TYPE=DEBUG -G "Ninja"
cmake -S . -B out/emscripten-debug -DCMAKE_BUILD_TYPE=DEBUG ^
	-DCMAKE_TOOLCHAIN_FILE=%EMSDK%/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake ^
	-G "Ninja"
cmake -S . -B out/emscripten-release -DCMAKE_BUILD_TYPE=RELEASE ^
	-DCMAKE_TOOLCHAIN_FILE=%EMSDK%/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake ^
	-G "Ninja"