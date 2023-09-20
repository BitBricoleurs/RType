echo Debut de l'installation des bibliotheques...
set LIBRARIES=sdl2-net
set VCPKG_DIR="vcpkg"

for %%L in (%LIBRARIES%) do (
    echo Telechargement et installation de la bibliotheque: %%L
    %VCPKG_DIR%\vcpkg install %%L
)

echo Fin de l'installation des bibliotheques.


echo Installation terminee!
