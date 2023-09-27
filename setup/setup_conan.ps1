# Script.ps1

# Mettre à jour le profil par défaut avec la détection automatique
conan profile detect --force

# Vérifiez si la commande précédente a réussi
if ($LASTEXITCODE -ne 0) {
    Write-Output "Erreur lors de la détection du profil Conan."
    exit 1
}

# Installer les dépendances spécifiées dans conanfile.txt
conan install setup/conanfile.txt --output-folder=build --build=missing

# Vérifiez si la commande précédente a réussi
if ($LASTEXITCODE -ne 0) {
    Write-Output "Erreur lors de l'installation des dépendances avec Conan."

