# Use the latest LTS version of Ubuntu as the base image
FROM archlinux:latest

RUN pacman --noconfirm -Syu && \
  pacman --noconfirm -S reflector
RUN reflector --country 'SG' > /etc/pacman.d/mirrorlist

# Install required packages
RUN pacman --noconfirm -S --needed base-devel git && \
    pacman --noconfirm -S --noconfirm cmake mingw-w64 wget sudo

RUN useradd -m -G wheel -s /bin/bash build && usermod -L build
RUN sed -Ei 's/^#\ (%wheel.*NOPASSWD.*)/\1/' /etc/sudoers

USER build
RUN     cd /tmp && git clone https://aur.archlinux.org/paru-bin.git && \
    cd paru-bin && \
    makepkg -si --noconfirm

# RUN paru -S --noconfirm mingw-w64-cmake
RUN sudo pacman-key --init
USER root
RUN echo -e "\n\n[ownstuff]\nServer = https://ftp.f3l.de/~martchus/\$repo/os/\$arch\nServer = https://martchus.no-ip.biz/repo/arch/\$repo/os/\$arch" >> /etc/pacman.conf
# RUN echo -e "\n\n[ownstuff]\nSigLevel = Optional TrustAll\nServer = https://martchus.no-ip.biz/repo/arch/$repo/os/$arch\nServer = https://ftp.f3l.de/~martchus/$repo/os/$arch\n" >> /etc/pacman.conf 
USER build
RUN sudo pacman-key --recv-keys B9E36A7275FC61B464B67907E06FE8F53CDC6A4C && \
sudo pacman-key --finger    b9e36a7275fc61b464b67907e06FE8F53CDC6A4C && \
sudo pacman-key --lsign-key b9e36a7275fc61b464b67907e06FE8F53CDC6A4C && \
sudo pacman-key --delete    b9e36a7275fc61b464b67907e06FE8F53CDC6A4C 
run sudo pacman -Sy && sudo pacman -S --noconfirm mingw-w64-freetype2 mingw-w64-cmake
run sudo pacman -Sy && sudo pacman -S --noconfirm mingw-w64-openal
run sudo pacman -Sy && sudo pacman -S --noconfirm mingw-w64-libvorbis
run sudo pacman -Sy && sudo pacman -S --noconfirm mingw-w64-flac

COPY . /game

# Build project using CMake
USER root
WORKDIR /game
RUN chmod +x /game/build_docker.sh
# VOLUME build /game/build
# RUN cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=/usr/share/mingw/toolchain-x86_64-w64-mingw32.cmake && \
#     cmake --build build

# Set the entry point to the built executable
ENTRYPOINT ["/game/build_docker.sh"]
