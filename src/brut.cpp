#include <iostream>
#include <string>
#include <algorithm> // Pour next_permutation
#include "../include/brut.hpp"
#include "../include/genetique.hpp"
using namespace std;

// Algorithme brute force pour le problème du voyageur de commerce
void tspBrut(vector<vector<double>>& distances) {
    int n = distances.size();
    vector<int> villes(n);
    for (int i = 0; i < n; ++i) {
        villes[i] = i;
    }

    double minCout = numeric_limits<double>::infinity();
    vector<int> meilleurChemin;

    // Essayer toutes les permutations des villes
    do {
        double coutActuel = distance_parcours(villes, distances);
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
    vector<vector<double>> distances = input_coordonnees();
    if (distances.empty()) {
        return 1; // Si les distances sont vides, quitter le programme
    }

    // Appliquer l'algorithme brut pour trouver la solution du TSP
    tspBrut(distances);

    return 0;
}
*/