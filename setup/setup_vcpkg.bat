@echo off

echo Début de l'installation des bibliothèques...
set LIBRARIES=sdl2-net
set VCPKG_DIR="vcpkg"

for %%L in (%LIBRARIES%) do (
    %VCPKG_DIR%\vcpkg install %%L
)

echo Installation terminée !
