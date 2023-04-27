# Use the latest LTS version of Ubuntu as the base image
FROM ubuntu:latest

# Install required packages
RUN apt-get update && \
    apt-get install -y cmake mingw-w64 git build-essential wget libfreetype6-dev
    # apt-get clean && \
    # rm -rf /var/lib/apt/lists/*

COPY . /game

# Build project using CMake
WORKDIR /game
RUN mkdir build
VOLUME build /game/build
RUN wget https://gist.githubusercontent.com/peterspackman/8cf73f7f12ba270aa8192d6911972fe8/raw/56ec269dc412a1055d00c4a810e6794283bc7dd4/mingw-w64-x86_64.cmake &&\
    cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=./mingw-w64-x86_64.cmake .. && \
    cmake --build build

# Set the entry point to the built executable
ENTRYPOINT ["./build/EverythingNMM.exe"]
