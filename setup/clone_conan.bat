@echo off

set LIBRARIES=raylib/3.7.0 glfw3/3.3.2

for %%i in (%LIBRARIES%) do (
    conan install %%i --build=missing
)

echo Installation terminée !
