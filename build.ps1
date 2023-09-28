if (-not (Test-Path ./build)) {
    New-Item -ItemType Directory -Force -Path ./build
}

cd ./build

cmake ..
cmake --build .