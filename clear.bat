@echo off
echo Nettoyage des fichiers et dossiers générés...

rd /s /q build
del /f /q conan-win-64.zip
del /f /q POCProgram
del /f /q POCProgram.exe
del /f /q POCProgram.pdb

echo Nettoyage terminé!
