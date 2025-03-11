#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

/*
HYPOTHESES DU MODELE : 
- Seules figurent dans le modèle les villes par lesquelles on doit passer (pas de villes de passage
non obligatoires)


- Chaque ville ne doit être visitée qu'une fois (sauf le départ auquel il faut revenir)
--> Il faudra essayer d'enlever cette hypothèse pour gérer les graphes étoilés

- Graphe complet, chaque ville est reliée à toutes les autres)
--> Pour se dégager facilement de cette hypothèse, mettre des distances très grandes pour les 
villes non connectées semble pertinent.
*/


//Individu = itinéraire
class Individu{
    public:
        vector<int> itineraire; //itinéraire effectif
        double adaptation; //adaptation = inverse de la distance de l'itinéraire

        //constructeur paramétrique
        Individu(vector<int> itineraire_,double adaptation_=0):
        itineraire(itineraire_),adaptation(adaptation_){};

        //constructeur par copie
        Individu(const Individu& autre):
        itineraire(autre.itineraire),adaptation(autre.adaptation){};

        //évaluation de l'itinéraire
        void evaluer(vector<vector<double>>& matrice_des_distances){
            adaptation = 1./distance_parcours(*this, matrice_des_distances);
        }

        //affichage de l'itinéraire
        void afficher(){
            auto it=(*this).itineraire.begin();
            while(it !=(*this).itineraire.end()){
                cout << *it << "-->";
                it++;
            }
            cout << endl << (*this).adaptation << endl;
        }
};

//Distance d'un itinéraire/parcours 
double distance_parcours(Individu I,vector<vector<double>>& matrice_des_distances){
    double dist = 0.;
    int n = I.itineraire.size();
    for(int i = 0; i < n-1;i++ ){
        dist += matrice_des_distances[I.itineraire[i]][I.itineraire[i+1]];
    }
    return dist;
}


// Population = ensemble d'itinéraires
class Population{
    public:
        vector<Individu> composition;
        double somme_adaptations; 

        void initialiser(int taille_population, int nombre_villes){
            composition.clear();
            // On crée un vecteur contenant toutes les villes par lesquelles on doit passer 
            vector<int> annuaire_villes;
            int i=0;
            while(i<nombre_villes){
                annuaire_villes.push_back(i);
                i++;
            }
            int j=0;
            while(j<taille_population){
                //On mélange notre annuaire aléatoirement
                random_shuffle(annuaire_villes.begin(),annuaire_villes.end());
                //On ajoute cette permutation aléatoire à la population
                composition.push_back(Individu(annuaire_villes));
                j++;
            }
        }

        void evaluer(vector<vector<double>>& matrice_des_distances){
            auto it = (*this).composition.begin();
            while(it != (*this).composition.end()){
                (*it).evaluer(matrice_des_distances);
            }
        }

        void afficher(){
            auto it = (*this).composition.begin();
            while(it != (*this).composition.end()){
                (*it).afficher();
            }
        }

        // trier en fonction de l'adaptation (tri décroissant)

        bool comparateur_selon_adaptation(Individu a, Individu b){
            return a.adaptation>b.adaptation;
        }

        void trier(){
            sort((*this).composition.begin(),(*this).composition.end(),comparateur_selon_adaptation);
        }
        


};


// Les opérateurs génétiques doivent proposer des chemins valides
// Donc chaque ville ne doit apparaître qu'une fois

// hybridation = croisement de deux composition
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


// mutation d'un individu
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

// sélection des reproducteurs
enum modes_selection_reproducteurs {ROULETTE, RANG, TOURNOI, EUGENISME};
Population selection_reproducteurs(const Population& adultes, enum modes_selection_reproducteurs mode_choisi = ROULETTE){
    Population reproducteurs;
    if(mode_choisi == ROULETTE){
        auto iterateur = adultes.composition.begin();
        int S = 0;
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
    }
    // Les trois autres modes de sélection des reproducteurs pourront être implémentés plus tard
    return reproducteurs;
}

//sélection des composition qui vont survivre 
enum modes_selection_pop_finale{ENFANTS_PRIORITAIRES, ELITISME};
Population selection_population_finale(const Population& parents, const Population& enfants, enum modes_selection_pop_finale mode_choisi = ENFANTS_PRIORITAIRES, int nombre_parents_survivants=0){
    Population nouvelle_generation;
    Population parents_classee=parents;
    parents_classee.trier();
    Population enfants_classee=enfants;
    enfants_classee.trier();
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
    return nouvelle_generation;
}


// Génération d'une matrice des distances à partir d'un input à faire
void algorithme_genetique(int max_generation, int taille_population, int nombre_villes,  vector<vector<double>> matrice_des_distances, int frequence_mutation=0.1){
    Population P;
    P.initialiser(taille_population,nombre_villes);
    P.evaluer(matrice_des_distances);
    int i = 0;
    while(i<max_generation){
        Population parents = selection_reproducteurs(P);

        
        Population enfants;
        while (enfants.composition.size() < taille_population) {
            Individu parent1 = parents.composition[rand() % parents.composition.size()];
            Individu parent2 = parents.composition[rand() % parents.composition.size()];
            auto [enfant1, enfant2] = hybridation(parent1, parent2);
            enfants.composition.push_back(enfant1);
            enfants.composition.push_back(enfant2);
        }

        int i=0;
        while(i < enfants.composition.size() * frequence_mutation){
            int index = rand() % enfants.composition.size();
            enfants.composition[index] = mutation(enfants.composition[index]);
        }

        P=selection_population_finale(parents,enfants);
        P.evaluer(matrice_des_distances);
    }


}

int main(){
    return 0;
}
 
