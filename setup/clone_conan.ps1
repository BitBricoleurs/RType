# Script.ps1

# Vérifier si Python est installé
if (-not (Get-Command python -ErrorAction SilentlyContinue)) {
    Write-Output "Python is required but not installed. Please install Python."
    exit 1
}

# Vérifier si pip est installé
if (-not (Get-Command pip -ErrorAction SilentlyContinue)) {
    Write-Output "pip is required but not installed. Please install pip."
    exit 1
}

# Installer Conan via pip
pip install conan
if ($LASTEXITCODE -ne 0) {
    Write-Output "Failed to install Conan using pip."
    exit 1
}

exit 0
