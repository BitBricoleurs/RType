# Script.ps1

# Vérifier si le dossier "build" n'existe pas
if (-not (Test-Path build)) {
    # Créer le dossier "build"
    New-Item -Type Directory -Path build

    # Exécuter les scripts
    & '.\setup\clone_conan.sh'
    & '.\setup\setup_conan.sh'
}

# Se déplacer dans le dossier "build" et exécuter CMake
cd build
& 'cmake' .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
& 'cmake' --build .
