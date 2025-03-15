#include <iostream>
#include "traitement_input.hpp"
//#include "brut.hpp"
#include "genetique.hpp"
//#include "affichage.hpp"

bool valider_matrice_distances(const vector<vector<double>>& matrice) {
    for (int i = 0; i < matrice.size(); i++) {
        for (int j = 0; j < matrice[i].size(); j++) {
            if (i != j && matrice[i][j] <= 0) { // Bloque les zéros et valeurs négatives
                cerr << "ERREUR: Distance invalide entre " << i << " et " << j << endl;
                return false;
            }
        }
    }
    return true;
}

int main()
{
    std::cout << "Hello world!" << std::endl;
    vector<vector<double>> adj = input_coordonnees("./src/input.txt");
    cout<<"Chargement de la matrice des distances : OK"<<endl;
    if (!valider_matrice_distances(adj)) {
        cerr << "Matrice des distances corrompue !" << endl;
        return 1;
    }
    algorithme_genetique(20,30,94,adj,0.1);
    return 0;
}
