@echo off
echo Cleaning up CMake generated files and folders...

:: Supprimer les dossiers générés par CMake
rd /s /q .cmake
rd /s /q client.dir
rd /s /q server.dir
rd /s /q Debug
rd /s /q POCProgram.dir
rd /s /q CMakeFiles
rd /s /q _deps
rd /s /q Testing

:: Supprimer les dossiers dans lib
cd lib
rd /s /q CMakeFiles
cd ..

:: Supprimer les dossiers spécifiques dans src
cd src
rd /s /q AudioEngine\AudioEngineLib.dir
rd /s /q GameEngine\GameEngine.dir
rd /s /q RenderEngine\RenderEngineLib.dir
cd ..

echo Clean up completed.
