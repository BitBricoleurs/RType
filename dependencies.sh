#!/bin/bash

# Vérifier la distribution Linux
if command -v lsb_release &> /dev/null; then
    DISTRO=$(lsb_release -si)
elif [ -f "/etc/fedora-release" ]; then
    DISTRO="Fedora"
else
    echo "Impossible de déterminer la distribution. Le script pourrait ne pas fonctionner correctement."
    exit 1
fi

install_debian_ubuntu() {
    sudo apt update
    sudo apt install -y python3 python3-pip
}

install_fedora() {
    sudo dnf install -y python3 python3-pip
}

install_centos() {
    sudo yum install -y python3 python3-pip
}

install_arch() {
    sudo pacman -Syu python python-pip
}

case $DISTRO in
    Ubuntu|Debian)
    install_debian_ubuntu
    ;;

    Fedora)
    install_fedora
    ;;

    CentOS)
    install_centos
    ;;

    Arch)
    install_arch
    ;;

    *)
    echo "Distribution non prise en charge ou impossible à déterminer."
    exit 1
    ;;
esac

# Vérifier si Python et pip sont bien installés
if command -v python3 &> /dev/null && command -v pip3 &> /dev/null; then
    echo "Python et pip ont été installés avec succès."
else
    echo "Erreur lors de l'installation de Python ou pip."
    exit 1
fi
