#include <iostream>
#include "traitement_input.hpp"
//#include "brut.hpp"
#include "genetique.hpp"
//#include "affichage.hpp"


int main()
{
    std::cout << "Hello world!" << std::endl;
    vector<vector<double>> adj = input_coordonnees("./src/input.txt");
    cout<<"Chargement de la matrice des distances : OK"<<endl;
    algorithme_genetique(5,6,94,adj,0.1);
    return 0;
}
