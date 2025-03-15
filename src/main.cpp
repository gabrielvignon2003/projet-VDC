#include <iostream>
#include "traitement_input.hpp"
//#include "brut.hpp"
#include "genetique.hpp"
//#include "affichage.hpp"


int main()
{
    std::cout << "Hello world!" << std::endl;
    vector<vector<double>> adj = input_coordonnees("input.txt");
    algorithme_genetique(5,100,3,adj,0.1);
    return 0;
}
