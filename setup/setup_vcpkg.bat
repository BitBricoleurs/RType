echo Debut de l'installation des bibliotheques...
set LIBRARIES=sdl2-net

for %%L in (%LIBRARIES%) do (
    echo Telechargement et installation de la bibliotheque: %%L
    vcpkg install %%L
)

echo Fin de l'installation des bibliotheques.


echo Installation terminee!
