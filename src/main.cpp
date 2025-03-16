#include <iostream>
#include "traitement_input.hpp"
#include <string>
#include "brut.hpp"
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

//input.txt : 94 villes
//input2.txt : 6 villes, bien pour comparaison avec la force brute
//input3.txt : 11 villes

int main(){
    string input="./src/input3.txt";
    int taille_population = 500;
    int max_generation = 3000;
    int nombre_villes= 11;
    double frequence_mutation = 0.03;
    int nombre_parents_survivants=250;

    cout << "Hello world!" << endl;
    vector<vector<double>> adj = input_coordonnees(input);
    cout<<"Chargement de la matrice des distances : OK"<<endl;
    if (!valider_matrice_distances(adj)) {
        cerr << "Matrice des distances corrompue !" << endl;
        return 1;
    }
    cout << "FORCE BRUTE" <<endl;
    tspBrut(adj);

    cout <<"GENETIQUE" <<endl;
    algorithme_genetique(max_generation, taille_population, nombre_villes, adj, frequence_mutation, nombre_parents_survivants);
    return 0;
}
