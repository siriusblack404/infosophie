#include <string>
#include <cstdlib>
#include <sstream>
#include <unistd.h>
#include <fstream>
#include "utils.h"

std::string get_username() {
    const char* user = getenv("USER");
    std::stringstream ss;
    ss << "Nom d'utilisateur : " << (user ? user : "inconnu") << "\n";
    return ss.str();
}

std::string get_hostname() {
    char hostname[1024];
    gethostname(hostname, 1024);
    std::stringstream ss;
    ss << "Nom de la machine : " << hostname << "\n";
    return ss.str();
}

std::string get_uptime() {
    std::stringstream ss;
    FILE* fp = popen("uptime", "r");
    if (fp) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), fp)) {
            ss << "Uptime : " << buffer;
        }
        pclose(fp);
    } else {
        ss << "Impossible de récupérer l'uptime.\n";
    }
    return ss.str();
}

std::string get_wifi_profiles() {
    std::stringstream ss;

    // Linux Desktop
    FILE* nmcli = popen("nmcli -t -f NAME c show 2>/dev/null", "r");
    if (nmcli) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), nmcli)) {
            ss << "Wi-Fi : " << buffer;
        }
        pclose(nmcli);
        return ss.str();
    }

    // Android / Termux
    std::ifstream wpa("/data/misc/wifi/wpa_supplicant.conf");
    if (wpa.is_open()) {
        std::string line;
        while (std::getline(wpa, line)) {
            ss << line << "\n";
        }
        wpa.close();
    } else {
        ss << "Aucun profil Wi-Fi trouvé (accès root requis ?)\n";
    }

    return ss.str();
}
