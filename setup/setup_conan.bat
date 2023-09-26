@echo off

set LIBRARIES=raylib/4.0.0

for %%i in (%LIBRARIES%) do (
    conan install %%i --build=missing
)

echo Installation terminée !
