#!/bin/bash

if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Installation pour macOS..."
    if ! command -v brew >/dev/null 2>&1; then
        echo "Homebrew n'est pas installé. Veuillez l'installer d'abord."
        exit 1
    fi
    brew install mesa libx11 libxcursor libxinerama libxrandr xinerama xcursor xorg libglu pkg-config
else
    if command -v apt >/dev/null 2>&1 ; then
        PACKAGE_MANAGER="apt"
    elif command -v dnf >/dev/null 2>&1 ; then
        PACKAGE_MANAGER="dnf"
    elif command -v pacman >/dev/null 2>&1 ; then
        PACKAGE_MANAGER="pacman"
    else
        echo "Gestionnaire de paquets non pris en charge."
        exit 1
    fi

    if [ "$PACKAGE_MANAGER" == "apt" ]; then
        sudo apt update
        sudo apt install -y libgl1-mesa-dev libx11-dev libxcursor-dev libxinerama-dev libxrandr-dev libasound2-dev xinerama xcursor xorg libglu1-mesa-dev pkg-config
    elif [ "$PACKAGE_MANAGER" == "dnf" ]; then
        sudo dnf install -y mesa-libGL-devel libX11-devel libXcursor-devel libXinerama-devel libXrandr-devel alsa-lib-devel xinerama xcursor xorg-x11-server libXi-devel libGLU pkg-config
    elif [ "$PACKAGE_MANAGER" == "pacman" ]; then
        sudo pacman -Syu --needed mesa libx11 libxcursor libxinerama libxrandr alsa-lib xorg-xineramaproto xorg-xcursor xorg-server libglu pkg-config
    fi
fi

mkdir -p build
cd build
cmake ..
