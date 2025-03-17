#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "../include/traitement_input.hpp"
using namespace std;

double distance(double i1, double j1, double i2, double j2) {
    return sqrt((i1 - i2) * (i1 - i2) + (j1 - j2) * (j1 - j2));
}


/*
Deux formes d'input peuvent être utiles selon les cas : 
- Un fichier input.txt avec les coordonnées géographiques de cette forme :
ville0 x0 y0
ville1 x1 y1
...
- Un fichier contenant directement les distances entre les villes : 
distance_0-0 distance_0-1 distance_0-2 ...
distance_1-0 distance_1-1 distance_1-2 ...
...            ...          ...

Par exemple, la distance routière entre deux villes ne correspond pas à la distance à vol d'oiseaux, il vaut mieux donc 
directement avoir un input.txt correspondant à la matrice des distances
*/


vector<vector<double>> input_coordonnees(string nom_fichier) {
    ifstream fichier(nom_fichier);
    if (!fichier) {
        cerr << "Erreur lors de l'ouverture du fichier !" << endl;
        return {};
    }
    
    string mot;
    vector<double> coordonnees;
    while (fichier >> mot) { // Lire mot par mot
        istringstream iss(mot);
        double nombre;
        if (iss >> nombre) {
            //cout << "Nombre détecté : " << nombre << endl;
            coordonnees.push_back(nombre);
        } 
        // else {
        //     cout << "Texte détecté : " << mot << endl;
        // }
    }
    
    vector<vector<double>> Adj;
    for (int i = 0; i < coordonnees.size(); i += 2) {
        vector<double> ligne;
        for (int j = 0; j < coordonnees.size(); j += 2) {
            if (j % 2 == 0) {
                ligne.push_back(distance(coordonnees[i], coordonnees[i+1], coordonnees[j], coordonnees[j+1]));
            }
        }
        Adj.push_back(ligne);
    }
    
    // Affichage de la matrice des distances
    // for (int i = 0; i < Adj.size(); i++) {
    //     for (int j = 0; j < Adj[i].size(); j++) {
    //         cout << "[" << Adj[i][j] << "]";
    //     }
    //     cout << endl;
    // }
    fichier.close();
    return Adj;
}

vector<vector<double>> input_distances(string nom_fichier) {
    ifstream fichier(nom_fichier);
    if (!fichier) {
        cerr << "Erreur lors de l'ouverture du fichier !" << endl;
        return {};
    }

    vector<vector<double>> distances;
    string mot;
    
    // Lire chaque ligne du fichier
    while (getline(fichier, mot)) {
        istringstream iss(mot);
        vector<double> ligne;
        
        // Lire chaque valeur sur la ligne
        while (iss >> mot) {
            // Chaque "mot" devrait être de la forme "distance" ou une valeur numérique
            if (mot.find("distance") == string::npos) {
                // Convertir la distance en nombre et l'ajouter à la ligne
                double distance_val = stod(mot); 
                ligne.push_back(distance_val);
            }
        }
        
        // Ajouter la ligne des distances à la matrice des distances
        distances.push_back(ligne);
    }

    fichier.close();
    return distances;
}
