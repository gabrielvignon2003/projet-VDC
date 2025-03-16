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
                cout << *it;
                if(it != (*this).itineraire.end()-1){
                    cout << "-->";
                }
                it++;
            }
            cout << endl << "Adaptation : " << (*this).adaptation << endl;
        }
};

// Population = ensemble d'itinéraires
class Population{
    public:
        vector<Individu> composition;

        // Initialisation de la population avec des individus commençant tous par la ville 0

    void initialiser(int taille_population, int nombre_villes){
        composition.clear();
        // On crée un vecteur contenant toutes les villes par lesquelles on doit passer 
        // Sauf la ville 0 qui sera fixée au début
        vector<int> annuaire_villes;
        for(int i = 1; i < nombre_villes; i++){
            annuaire_villes.push_back(i);
        }
        
        int j = 0;
        while(j < taille_population){
            // On crée un nouvel itinéraire qui commence toujours par la ville 0
            vector<int> route;
            route.push_back(0); // Toujours commencer par la ville 0
            
            // On mélange notre annuaire aléatoirement (seulement les villes de 1 à n-1)
            random_shuffle(annuaire_villes.begin(), annuaire_villes.end());
            
            // On ajoute les villes mélangées après la ville 0
            for(int ville : annuaire_villes){
                route.push_back(ville);
            }
            
            // On ajoute cette permutation aléatoire à la population
            composition.push_back(Individu(route));
            j++;
        }
    }

        
        //Fonction qui met à jour tous les attributs adaptation des individus de la population
        void evaluer(vector<vector<double>>& matrice_des_distances){
            auto it = (*this).composition.begin();
            while(it != (*this).composition.end()){
                (*it).evaluer(matrice_des_distances);
                it++;
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

double distance_parcours(Individu, const vector<vector<double>>&);

pair<Individu, Individu> hybridation(const Individu&, const Individu&);

Individu mutation(Individu);

enum modes_selection_reproducteurs {ROULETTE, RANG, TOURNOI, EUGENISME};
Population selection_reproducteurs(const Population&, enum modes_selection_reproducteurs);

enum modes_selection_pop_finale{ENFANTS_PRIORITAIRES, ELITISME};
Population selection_population_finale(const Population&, const Population&, enum modes_selection_pop_finale, int); 

void algorithme_genetique(int, int, int,vector<vector<double>>, double, int);

#endif
