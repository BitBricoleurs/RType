#!/bin/bash

# Mettre à jour le profil par défaut avec la détection automatique
conan profile detect --force

conan config set general.tools.system.package_manager:mode=install
# Vérifiez si la commande précédente a réussi
if [ $? -ne 0 ]; then
    echo "Erreur lors de la détection du profil Conan."
    exit 1
fi

# Installer les dépendances spécifiées dans conanfile.txt

conan install setup/conanfile.txt --output-folder=build --build=missing

# Vérifiez si la commande précédente a réussi
if [ $? -ne 0 ]; then
    echo "Erreur lors de l'installation des dépendances avec Conan."
    exit 1
fi

exit 0
