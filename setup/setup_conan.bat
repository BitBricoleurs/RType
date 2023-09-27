@echo off

REM Chemin vers l'exécutable Conan
SET CONAN_PATH=build\conan.exe

REM Vérifie si Conan existe au chemin spécifié
if not exist "%CONAN_PATH%" (
    echo Conan n'a pas été trouvé à "%CONAN_PATH%".
    exit /b 1
)

REM Mettre à jour le profil par défaut avec la détection automatique
"%CONAN_PATH%" profile detect --force

REM Vérifiez si la commande précédente a réussi
if %ERRORLEVEL% neq 0 (
    echo Erreur lors de la détection du profil Conan.
    exit /b 1
)

REM Installer les dépendances spécifiées dans conanfile.txt
"%CONAN_PATH%" install setup\conanfile.txt --output-folder=build --build=missing -c tools.system.package_manager:mode=install

REM Vérifiez si la commande précédente a réussi
if %ERRORLEVEL% neq 0 (
    echo Erreur lors de l'installation des dépendances avec Conan.
    exit /b 1
)

exit /b 0
