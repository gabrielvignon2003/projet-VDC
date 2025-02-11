#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
using namespace std;
#include "genetique.cpp"

double distance_parcours(Individu I,vector<vector<double>> Matrice){
    double dist = 0.;
    int n = I.itineraire.size();
    for(int i = 0; i < n-1;i++ ){
        dist += Matrice[I.itineraire[i]][I.itineraire[i+1]];
    }
    return dist;
}