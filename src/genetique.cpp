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


enum modes_selection_reproducteurs {ROULETTE, RANG, TOURNOI, EUGENISME};
Population selection_reproducteurs(const Population& adultes, enum modes_selection_reproducteurs mode_choisi = ROULETTE){
    if(mode_choisi == ROULETTE){
        auto iterateur = adultes.composition.begin();
        int S = 0;
        Population reproducteurs;
        while(iterateur != adultes.composition.end()){
            S = S + (*iterateur).adaptation;
            iterateur++;
        }
        while(reproducteurs.composition.size()<adultes.composition.size()){
            int r = rand() % S;
            int somme_cumulee=0;
            iterateur = adultes.composition.begin();
            while(somme_cumulee<=r && iterateur != adultes.composition.end()){
                somme_cumulee=somme_cumulee+(*iterateur).adaptation;
                if(somme_cumulee>=r){
                    break;
                }
                iterateur++;
                
            }
            reproducteurs.composition.push_back(*iterateur);
        }
        return reproducteurs;
    }
    // Les trois autres modes de sélection des reproducteurs pourront être implémentés plus tard

}

Individu minorant_population(const Population& population_en_vrac){
    auto iterateur = population_en_vrac.composition.begin();
    Individu minorant = *iterateur;
    while(iterateur != population_en_vrac.composition.end()){
        if((*iterateur).adaptation<minorant.adaptation){
            minorant = *iterateur;
        }
        iterateur++;
    }
    return minorant;()
}


Population classement_population(const Population& population_en_vrac){
    Population temp(population_en_vrac);
    Population population_classee;
    int i=0;
    while(i<population_en_vrac.composition.size()){
        population_classee.composition.push_back(minorant_population(temp));
        temp.composition.erase(minorant_population(temp));
        i++;
    }
    
}

enum modes_selection_pop_finale{ENFANTS_PRIORITAIRES, ELITISME};
Population selection_population_finale(const Population& parents, const Population& enfants, enum modes_selection_pop_finale mode_choisi = ENFANTS_PRIORITAIRES, int nombre_parents_survivants=0){
    Population nouvelle_generation;
    Population parents_classee=classement_population(parents);
    Population enfants_classee=classement_population(enfants);
    if(mode_choisi == ENFANTS_PRIORITAIRES){
        return enfants;
    }
    else if(mode_choisi == ELITISME){
        int i=0;
        while(i<nombre_parents_survivants){
            nouvelle_generation.composition.push_back(parents_classee.composition[i]);
            i++;
        }
        int j=0;
        while(i+j<parents_classee.composition.size()){
            nouvelle_generation.composition.push_back(enfants_classee.composition[j]);
            j++;
        }

    }

    // L'eugénisme pourra être implanté plus tard 
}

int main(){
    return 0;
}
 
