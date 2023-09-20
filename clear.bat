@echo off
echo Nettoyage des fichiers et dossiers générés...

rd /s /q .idea
rd /s /q cmake-build-debug
rd /s /q x64
rd /s /q CmakeFiles
del /f /q CMakeCache.txt
del /f /q ALL_BUILD.vcxproj
del /f /q ALL_BUILD.vcxproj.filters
del /f /q cmake_install.cmake
del /f /q RType.sln
del /f /q ZERO_CHECK.vcxproj
del /f /q ZERO_CHECK.vcxproj.filters
del /f /q RType.exe
del /f /q Rtype.pdb
del /f /q SDL2d.dll

echo Nettoyage récursif des fichiers CMake dans src...
for /r src %%i in (CMakeFiles) do (
    if exist "%%i" rd /s /q "%%i"
)
for /r src %%i in (cmake_install.cmake) do (
    if exist "%%i" del /f /q "%%i"
)
for /r src %%i in (*.vcxproj) do (
    if exist "%%i" del /f /q "%%i"
)
for /r src %%i in (*.vcxproj.filters) do (
    if exist "%%i" del /f /q "%%i"
)
for /r src %%i in (Debug) do (
    if exist "%%i" rd /s /q "%%i"
)
for /r src %%i in (RType.dir) do (
    if exist "%%i" rd /s /q "%%i"
)

echo Nettoyage terminé!
