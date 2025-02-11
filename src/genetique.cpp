#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include "fonction_adaption.cpp"
using namespace std;

class Individu{
    public:
        vector<int> villes;
        int depart;
        vector<int> itineraire;
        double adaptation;

        //constructeur paramétrique
        Individu(vector<int> villes_, int depart_, vector<int> itineraire_,double adaptation_):
        villes(villes_),depart(depart_),itineraire(itineraire_),adaptation(adaptation_){};
        
        //constructeur par copie
        Individu(const Individu& autre):villes(autre.villes),depart(autre.depart),
        itineraire(autre.itineraire),adaptation(autre.adaptation){};
};

class Population{
    public:
        int taille;
        vector<Individu> composition;
};

pair<Individu,Individu> hybridation(Individu& papa, Individu& maman){
    Individu enfant_pm(maman);
    Individu enfant_mp(maman);
    srand(time(0));
    int separation=rand()%enfant_pm.itineraire.size()+1;
    int i=0;
    while(i<separation){
        enfant_pm.itineraire[i]=papa.itineraire[i];
    }
    i=separation;
    while(i<enfant_pm.itineraire.size()){
        enfant_mp.itineraire[i]=papa.itineraire[i];
        i++;
    }

    pair<Individu,Individu> fratrie(enfant_pm,enfant_mp);

    return fratrie;
    
    
}



Individu mutation(Individu parent){
    srand(time(0));
    int k = 1 + rand() % (parent.itineraire.size()-2);
    int l = 1 + rand() % (parent.itineraire.size()-2);
    Individu enfant(parent);
    enfant.itineraire[l] = parent.itineraire[k];
    enfant.itineraire[l-1] = parent.itineraire[k+1];
    enfant.itineraire[k] = parent.itineraire[l];
    enfant.itineraire[k+1] = parent.itineraire[l-1];
    return enfant;
}

int distance_population(Population& P){

    int S = 0;
    auto it = reproducteurs.composition.begin();
    while(it!=reproducteurs.composition.end()){
        S+=distance_parcours(it);
        it++;
    }
    return S;
}

// sélection par roulette
Population selection_roulette(Population& P){
    Population reproducteurs;
    int S = 0;
    auto it = reproducteurs.composition.begin();
    while(it!=reproducteurs.composition.end()){
        S+=distance_parcours(it);
        it++;
    }
    int r = rand()%S;
    int somme = 0;
    while(somme<r){
        int j = rand()%(reproducteurs.composition.size()-1);
        somme+=distance_parcours(reproducteurs.composition[j]);
    }

}

Individu adaptation_max(Population&P){
    auto it=P.composition.begin();
    Individu max=*it;
    while(it!=P.end()){
        if(distance_parcours(*it)<distance_parcours(*(it+1))){
            max=*(it+1);
        }
        it++;
    }
    return max
}

// sélection par rang
Population selection_rang(Population& P){
    Population reproducteurs=P;
    int S=distance_population(reproducteurs);
    while(distance_population(reproducteurs)>S){
        reproducteurs.pop(adaptation_max(P));
    }
    return reproducteurs;
}

int main(){
    return 0;
}
 