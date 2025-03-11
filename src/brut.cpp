#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm> // Pour next_permutation

using namespace std;

double distance(double i1, double j1, double i2, double j2) {
    return sqrt((i1 - i2) * (i1 - i2) + (j1 - j2) * (j1 - j2));
}

vector<vector<double>> input(string fichier_texte) {
    std::ifstream fichier(fichier_texte);
    if (!fichier) {
        std::cerr << "Erreur lors de l'ouverture du fichier !" << std::endl;
        return {};
    }
    
    std::string mot;
    std::vector<double> coordonnees;
    while (fichier >> mot) { // Lire mot par mot
        std::istringstream iss(mot);
        double nombre;
        if (iss >> nombre) {
            std::cout << "Nombre détecté : " << nombre << std::endl;
            coordonnees.push_back(nombre);
        } else {
            std::cout << "Texte détecté : " << mot << std::endl;
        }
    }
    
    vector<vector<double>> Adj;
    for (int i = 0; i < coordonnees.size(); i += 2) {
        std::vector<double> ligne;
        for (int j = 0; j < coordonnees.size(); j += 2) {
            if (j % 2 == 0) {
                ligne.push_back(distance(coordonnees[i], coordonnees[i+1], coordonnees[j], coordonnees[j+1]));
            }
        }
        Adj.push_back(ligne);
    }
    
    // Affichage de la matrice des distances
    for (int i = 0; i < Adj.size(); i++) {
        for (int j = 0; j < Adj[i].size(); j++) {
            cout << "[" << Adj[i][j] << "]";
        }
        cout << endl;
    }
    fichier.close();
    return Adj;
}

// Fonction pour calculer le coût d'un chemin
double calculerCout(const vector<int>& chemin, const vector<vector<double>>& distances) {
    double coutTotal = 0;
    for (int i = 0; i < chemin.size() - 1; i++) {
        coutTotal += distances[chemin[i]][chemin[i + 1]];
    }
    coutTotal += distances[chemin.back()][chemin.front()]; // Retour au point de départ
    return coutTotal;
}

// Algorithme brute force pour le problème du voyageur de commerce
void tspBrut(const vector<vector<double>>& distances) {
    int n = distances.size();
    vector<int> villes(n);
    for (int i = 0; i < n; ++i) {
        villes[i] = i;
    }

    double minCout = numeric_limits<double>::infinity();
    vector<int> meilleurChemin;

    // Essayer toutes les permutations des villes
    do {
        double coutActuel = calculerCout(villes, distances);
        if (coutActuel < minCout) {
            minCout = coutActuel;
            meilleurChemin = villes;
        }
    } while (next_permutation(villes.begin() + 1, villes.end())); // On ne permute pas la première ville

    // Afficher le résultat
    cout << "Chemin optimal: ";
    for (int i = 0; i < meilleurChemin.size(); ++i) {
        cout << meilleurChemin[i] << " ";
    }
    cout << endl;
    cout << "Coût total: " << minCout << endl;
}

/*
int main() {
    // Lire les coordonnées des villes à partir du fichier
    vector<vector<double>> distances = input();
    if (distances.empty()) {
        return 1; // Si les distances sont vides, quitter le programme
    }

    // Appliquer l'algorithme brut pour trouver la solution du TSP
    tspBrut(distances);

    return 0;
}
    */
