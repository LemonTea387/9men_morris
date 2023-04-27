# Use the latest LTS version of Arch Linux as the base image
FROM archlinux:latest

# Get Singapore Mirrors for faster installation of packages
RUN pacman --noconfirm -Syu && \
  pacman --noconfirm -S reflector
RUN reflector --country 'SG' > /etc/pacman.d/mirrorlist

# Install required packages
RUN pacman --noconfirm -S --needed base-devel git && \
    pacman --noconfirm -S --noconfirm cmake mingw-w64 wget sudo

# Create temporary non-root user with sudo privileges called "build"
RUN useradd -m -G wheel -s /bin/bash build && usermod -L build
RUN sed -Ei 's/^#\ (%wheel.*NOPASSWD.*)/\1/' /etc/sudoers

# Add custom repository with binary builds (so no need to build from source)
RUN sudo pacman-key --init
USER root
RUN echo -e "\n\n[ownstuff]\nServer = https://ftp.f3l.de/~martchus/\$repo/os/\$arch\nServer = https://martchus.no-ip.biz/repo/arch/\$repo/os/\$arch" >> /etc/pacman.conf

# Add the keys for the custom repo
USER build
RUN sudo pacman-key --recv-keys B9E36A7275FC61B464B67907E06FE8F53CDC6A4C && \
sudo pacman-key --finger    b9e36a7275fc61b464b67907e06FE8F53CDC6A4C && \
sudo pacman-key --lsign-key b9e36a7275fc61b464b67907e06FE8F53CDC6A4C && \
sudo pacman-key --delete    b9e36a7275fc61b464b67907e06FE8F53CDC6A4C 

# Install cross-compiler packages
RUN sudo pacman -Sy && sudo pacman -S --noconfirm mingw-w64-freetype2 mingw-w64-cmake
RUN sudo pacman -Sy && sudo pacman -S --noconfirm mingw-w64-openal
RUN sudo pacman -Sy && sudo pacman -S --noconfirm mingw-w64-libvorbis
RUN sudo pacman -Sy && sudo pacman -S --noconfirm mingw-w64-flac

# Copy over the source code to the container
# NOTE: If you modifiy the code, you need to rebuild the container.
# This dockerfile is meant for easy building, not for development
COPY . /game

# Make the build_docker.sh script executable
USER root
WORKDIR /game
RUN chmod +x /game/build_docker.sh

# Set the entry point to the built executable
ENTRYPOINT ["/game/build_docker.sh"]
