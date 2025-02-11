#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
using namespace std;
#include "genetique.cpp"





//Une valeur plus faible de la fonction d'adaption signifie une meilleur adaptation de l'individu.
double DistanceParcours(Individu I,vector<vector<double>> &Matrice){
    double dist = 0.;
    int n = I.itineraire.size();
    for(int i = 0; i < n-1;i++ ){
        dist += Matrice[I.itineraire[i]][I.itineraire[i+1]];
    }
    return dist;
}