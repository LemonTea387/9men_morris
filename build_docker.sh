#!/usr/bin/env bash
# For intellisense, toggle CMAKE_EXPORT_COMPILE_COMMANDS=ON
# For debugging, toggle CMAKE_BUILD_TYPE=Debug
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=/usr/share/mingw/toolchain-x86_64-w64-mingw32.cmake
cmake --build build
mkdir -p build/clean_build
cp build/EverythingNMM.exe build/clean_build
cp -r build/_deps/sfml-build/lib/*.dll build/clean_build
cp -r assets build/clean_build
cp -r /usr/x86_64-w64-mingw32/bin/*.dll build/clean_build

