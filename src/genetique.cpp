#include <iostream>
#include <cstdlib>
#include <time>
#include <vector>
#include <pair>
using namespace std;

class Individu{

    private:
        vector<int> villes;
        int depart;
        vector<int> itineraire;
        double adaptation;
    public: 
        Individu(const Individu& autre):villes(autre.villes),depart(autre.depart),
        itineraire(autre.itineraire),adaptation(autre.adaptation){};
};

class Population{
    private:
        int taille;
        vector<Individu> composition;
};

pair<Individu> hybridation(Individu& papa, Individu& maman){
    Individu enfant_pm(maman);
    Individu enfant_mp(maman);
    srand(time(0));
    separation=rand()%enfant.itineraire.size()+1;
    int i=0;
    while(i<l){
        enfant_pm[i]=papa[i];
    }
    int i=separation;
    while(i<enfant.itineraire.size()){
        enfant_mp[i]=papa[i];
        i++;
    }

    pair<Individu> fratrie;
    fratrie.first=enfant_pm;
    fratrie.second=enfant_mp;

    return fratrie;
    
    
}

Individu mutation(Individu parent){
    std::srand(std::time(0));
    int k = 1 + std::rand() % (itineraire.size()-2);
    int l = 1 + std::rand() % (itineraire.size()-2);
    Individu enfant(parent);
    enfant.itineraire[l] = parent.itineraire[k];
    enfant.itineraire[l-1] = parent.itineraire[k+1];
    enfant.itineraire[k] = parent.itineraire[l];
    enfant.itineraire[k+1] = parent.itineraire[l-1];
    return enfant;
}

int main(){
    return 0;
}
