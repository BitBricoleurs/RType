#!/bin/bash

if ! command -v pip &> /dev/null; then
    echo "pip is required but not installed. Please install pip."
    exit 1
fi

# Install Conan

pip install conan
if [ $? -ne 0 ]; then
    echo "Failed to install Conan using pip."
    exit 1
fi

exit 0