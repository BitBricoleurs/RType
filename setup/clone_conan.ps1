# Crée le dossier "build" s'il n'existe pas
if (-not (Test-Path .\build)) {
    New-Item -Path .\build -ItemType Directory
}

# Télécharge l'archive Conan depuis le dernier release sur GitHub
Invoke-WebRequest -Uri "https://github.com/conan-io/conan/releases/latest/download/conan-win-64.zip" -OutFile conan-win-64.zip

# Vérifie si l'archive a été correctement téléchargée
if (-not (Test-Path conan-win-64.zip)) {
    Write-Error "Erreur lors du téléchargement de l'archive Conan."
    exit 1
}

# Extrait l'archive dans le dossier "build"
Expand-Archive .\conan-win-64.zip -DestinationPath .\build

# Vérifie si Conan a été correctement extrait
if (-not (Test-Path .\build\conan.exe)) {
    Write-Error "Erreur lors de l'extraction de Conan dans le dossier build."
    exit 1
}

Write-Output "Conan a été correctement téléchargé et extrait dans le dossier build."
