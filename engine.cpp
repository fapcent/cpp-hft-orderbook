#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <sstream>

// --- STRUCTURES ---
struct Order {
    int id;
    std::string trader_id;
    std::string side; // "BUY" ou "SELL"
    double price;
    int quantity;
};

// --- GESTION DE LA SÉCURITÉ (Anti-Flood) ---
struct TraderStats {
    int order_count;
    std::chrono::steady_clock::time_point last_reset;
    bool is_banned;
};

std::map<std::string, TraderStats> security_table;

// Fonction de sécurité : Retourne TRUE si le trader est bloqué
bool is_spamming(const std::string& trader_id) {
    auto now = std::chrono::steady_clock::now();
    
    // Si le trader n'existe pas, on l'ajoute
    if (security_table.find(trader_id) == security_table.end()) {
        security_table[trader_id] = {0, now, false};
    }

    TraderStats& stats = security_table[trader_id];

    if (stats.is_banned) return true;

    // Reset du compteur chaque seconde
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - stats.last_reset).count();
    if (elapsed > 1000) {
        stats.order_count = 0;
        stats.last_reset = now;
    }

    stats.order_count++;

    // SEUIL DE DÉTECTION : Plus de 100 ordres par seconde = BAN
    if (stats.order_count > 100) {
        stats.is_banned = true;
        std::cout << "[SECURITY] 🚨 ALERTE: Trader " << trader_id << " banni pour Quote Stuffing !" << std::endl;
        return true;
    }

    return false;
}

// --- MOTEUR PRINCIPAL ---
int main() {
    std::string line;
    int processed_orders = 0;

    std::cout << "[ENGINE] Moteur de Matching C++ démarré. En attente d'ordres..." << std::endl;

    // Boucle infinie qui lit les ordres ligne par ligne
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> parts;

        while (std::getline(ss, segment, ',')) {
            parts.push_back(segment);
        }

        if (parts.size() < 4) continue;

        std::string trader = parts[0];
        std::string side = parts[1];
        double price = std::stod(parts[2]);
        int qty = std::stoi(parts[3]);

        // 1. VÉRIFICATION DE SÉCURITÉ (Avant de traiter l'ordre)
        if (is_spamming(trader)) {
            // On ignore silencieusement ou on logue le rejet
            continue; 
        }

        // 2. TRAITEMENT (Simulation d'ajout au carnet)
        processed_orders++;
        
        // Pour la démo, on affiche juste un log tous les 50 ordres pour ne pas spammer la console
        if (processed_orders % 50 == 0) {
            std::cout << "[MARKET] Ordre accepté de " << trader << " | " << side << " " << qty << " @ " << price << std::endl;
        }
    }

    return 0;
}