#!/bin/bash

# Prompt the user to select a package manager
echo "Enter your package manager (apt, yum, pacman):"
read package_manager

# Install git based on the selected package manager
if [ "$package_manager" == "apt" ]; then
    sudo apt update && sudo apt install -y git gcc
elif [ "$package_manager" == "yum" ]; then
    sudo yum install -y git gcc
elif [ "$package_manager" == "pacman" ]; then
    sudo pacman -Syu --noconfirm git gcc
else
    echo "Unsupported package manager. Please use apt, yum, or pacman."
    exit 1
fi

# Clone the repository
git clone https://github.com/Calestial2/Txtmax.git

# Navigate to the Txtmax directory and compile the program
cd Txtmax || { echo "Failed to enter Txtmax directory."; exit 1; }
cd versions || { echo "Failed to enter versions directory."; exit 1; }
gcc txtmax9.c -o txtmax9

# Run the compiled program
./txtmax9
