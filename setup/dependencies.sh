#!/bin/bash

if [[ "$(uname)" == "Darwin" ]]; then
    echo "macOS detected. Installing required tools using Homebrew..."

    if ! command -v brew >/dev/null 2>&1; then
        echo "Homebrew not found. Installing..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi

    brew install rpm dpkg
    brew install cmake llvm
    ln -sf "$(brew --prefix llvm)/bin/clang-tidy" "/usr/local/bin/clang-tidy"
    ln -sf "$(brew --prefix llvm)/bin/clang-format" "/usr/local/bin/clang-format"
    exit 0
fi

if command -v apt-get >/dev/null 2>&1; then
    echo "apt-get detected. Installing required tools..."
    sudo apt-get update
    sudo apt-get install -y g++ cmake clang-tidy clang-format xorg-dev dpkg rpm
    exit 0
fi

if command -v pacman >/dev/null 2>&1; then
    echo "pacman detected. Installing required tools..."
    sudo pacman -Syu --noconfirm g++ cmake clang dpkg rpm
    exit 0
fi

if command -v dnf >/dev/null 2>&1; then
    echo "dnf detected. Installing required tools..."
    sudo dnf install -y libXcursor-devel libXi-devel libXinerama-devel libXrandr-devel cmake clang-tools-extra gcc-c++ make cmake dpkg rpm-build
    exit 0
fi

echo "Unsupported package manager or OS"
exit 12
