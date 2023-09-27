@echo off

REM Vérifie si le dossier "build" n'existe pas
if not exist "build\" (
    REM Crée le dossier "build"
    mkdir build

    REM Exécute les scripts de configuration de Conan
    powershell -ExecutionPolicy Bypass -File setup\clone_conan.ps1
    call setup\setup_conan.bat
)

cd build
call cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
call cmake --build .
