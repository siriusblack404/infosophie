#include "browser_dump.h"
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

std::string dump_browser_passwords() {
    std::stringstream ss;
    ss << "[*] Recherche de bases SQLite contenant des mots de passe\n";

    std::vector<std::string> paths = {
        std::string(getenv("HOME")) + "/.config/google-chrome/Default/Login Data",
        std::string(getenv("HOME")) + "/.config/chromium/Default/Login Data",
        std::string(getenv("HOME")) + "/.config/brave/Default/Login Data",
        std::string(getenv("HOME")) + "/.mozilla/firefox/"
    };

    for (const auto& path : paths) {
        if (fs::exists(path)) {
            ss << "[+] Trouvé : " << path << "\n";
        }
    }

    ss << "⚠️ Extraction SQLite/Décryptage non incluse ici (peut être ajoutée)\n";

    return ss.str();
}
