#!/bin/bash

command -v conan >/dev/null 2>&1 || {
    echo "Conan is not installed. Installing..."
    pip install conan
}
