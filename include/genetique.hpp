#ifndef GENETIQUE_HPP
#define GENETIQUE_HPP

#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

//Individu = itinéraire
class Individu{
    public:
        vector<int> itineraire; //itinéraire effectif
        double adaptation; //adaptation = inverse de la distance de l'itinéraire
        /*
        Plus l'adaptation est grande, meilleur est le chemin.
        */
        //constructeur paramétrique
        Individu(vector<int> itineraire_,double adaptation_=0):
        itineraire(itineraire_),adaptation(adaptation_){};

        //constructeur par copie
        Individu(const Individu& autre):
        itineraire(autre.itineraire),adaptation(autre.adaptation){};

        void evaluer(vector<vector<double>>&);

        //affichage de l'itinéraire
        void afficher(){
            auto it=(*this).itineraire.begin();
            while(it !=(*this).itineraire.end()){
                cout << *it << "-->";
                it++;
            }
            cout << endl << "Adaptation : " << (*this).adaptation << endl;
        }
};

// Population = ensemble d'itinéraires
class Population{
    public:
        vector<Individu> composition;

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
        
        //Fonction qui met à jour tous les attributs adaptation des individus de la population
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
        static bool comparateur_selon_adaptation(const Individu& a, const Individu& b){
            return a.adaptation>b.adaptation;
        }

        void trier(){
            sort((*this).composition.begin(),(*this).composition.end(),comparateur_selon_adaptation);
        }

        Individu majorant(){
            Population copie(*this);
            copie.trier();
            return copie.composition[0];

        }
        


};

double distance_parcours(Individu, vector<vector<double>>&);

pair<Individu, Individu> hybridation(const Individu&, const Individu&);

Individu mutation(Individu);

enum modes_selection_reproducteurs {ROULETTE, RANG, TOURNOI, EUGENISME};
Population selection_reproducteurs(const Population&, enum modes_selection_reproducteurs);

enum modes_selection_pop_finale{ENFANTS_PRIORITAIRES, ELITISME};
Population selection_population_finale(const Population&, const Population&, enum modes_selection_pop_finale, int); 

void algorithme_genetique(int, int, int,vector<vector<double>>, int);

#endif
