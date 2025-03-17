#include <cstdlib>
#include <ctime>
#include <utility>
#include "../include/genetique.hpp"
using namespace std;


/*
HYPOTHESES DU MODELE : 
- Seules figurent dans le modèle les villes par lesquelles on doit passer (pas de villes de passage
non obligatoires)

- Graphe complet, chaque ville est reliée à toutes les autres)
--> Pour se dégager facilement de cette hypothèse, mettre des distances très grandes pour les 
villes non connectées semble pertinent.

- Chaque ville ne doit être visitée qu'une fois (sauf le départ auquel il faut revenir)
--> Il faudra essayer d'enlever cette hypothèse pour gérer les graphes étoilés
*/

// Distance d'un itinéraire/parcours 
double distance_parcours(Individu I, const vector<vector<double>>& matrice_des_distances) {
    if (I.itineraire.size() <= 1) return 0.0;  // ✅ Cas d'une seule ville
    double dist = 0.;
    int n = I.itineraire.size();
    for (int i = 0; i < n - 1; i++) {
        int j = (i + 1) % n;
        dist += matrice_des_distances[I.itineraire[i]][I.itineraire[j]];
    }
    return dist;
}

// Evaluation de l'itinéraire
void Individu::evaluer(vector<vector<double>>& matrice_des_distances) {
    if (itineraire.size() == 1) {
        adaptation = 1.0;  // ✅ Cas où il n'y a qu'une seule ville → meilleure adaptation possible
        return;
    }

    double dist = distance_parcours(*this, matrice_des_distances);
    if (dist <= 1e-7) {
        adaptation = 0.0;
    } else {
        adaptation = 1.0 / dist;
    }
}

// Les opérateurs génétiques doivent proposer des chemins valides
// Donc chaque ville ne doit apparaître qu'une fois

// hybridation = croisement de deux composition
// pair<Individu, Individu> hybridation(const Individu& maman, const Individu& papa) {
//     int size = maman.itineraire.size();
//     //Initialise les enfants en mettant des -1 partout
//     vector<int> itineraire_enfant1(size, -1);
//     vector <int> itineraire_enfant2(size, -1);
//     Individu enfant1(itineraire_enfant1,0);
//     Individu enfant2(itineraire_enfant2,0);

//     // Génération d’un point de coupure aléatoire
//     random_device rd;
//     mt19937 gen(rd());
//     uniform_int_distribution<int> dist(1, size - 2); // Assurer qu’il y a bien une partie après le point
//     int cut = dist(gen);

//     // Copier la première partie des parents vers les enfants
//     for (int i = 0; i <= cut; i++) {
//         enfant1.itineraire[i] = maman.itineraire[i];
//         enfant2.itineraire[i] = papa.itineraire[i];
//     }

//     // Remplir le reste avec les éléments non encore utilisés
//     int index1 = cut + 1;
//     int index2 = cut + 1;
//     for (int i = 0; i < size; i++) {
//         int gene2 = papa.itineraire[i];
//         int gene1 = maman.itineraire[i];

//         if (find(enfant1.itineraire.begin(), enfant1.itineraire.end(), gene2) == enfant1.itineraire.end()) {
//             enfant1.itineraire[index1++] = gene2;
//         }
//         if (find(enfant2.itineraire.begin(), enfant2.itineraire.end(), gene1) == enfant2.itineraire.end()) {
//             enfant2.itineraire[index2++] = gene1;
//         }
//     }

//     return {enfant1, enfant2};
// }

pair<Individu, Individu> hybridation(const Individu& maman, const Individu& papa) {
    int size = maman.itineraire.size();
    vector<int> enfant1(size, -1), enfant2(size, -1);

    enfant1[0]=0;
    enfant2[0]=0;

    // Génération aléatoire de debut et fin AVANT la lambda
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, size - 2);
    int debut = dist(gen);
    int fin = dist(gen);
    if (debut > fin) swap(debut, fin);

    // Capture de debut et fin dans la lambda ([debut, fin, size])
    auto remplir_enfant = [debut, fin, size](const Individu& parent, vector<int>& enfant) {
        int index = (fin + 1) % size;
        for (int ville : parent.itineraire) {
            if (index == 0) index = 1; // Sauter l'indice 0
            if (find(enfant.begin(), enfant.end(), ville) == enfant.end()) {
                enfant[index] = ville;
                index = (index + 1) % size;
                if (index == debut) index = (fin + 1) % size;
                if (index == 0) index = 1; // Sauter l'indice 0
            }
        }
    };

    // Remplissage des enfants
    for (int i = debut; i <= fin; i++) {
        enfant1[i] = maman.itineraire[i];
        enfant2[i] = papa.itineraire[i];
    }

    remplir_enfant(papa, enfant1);
    remplir_enfant(maman, enfant2);

    return {Individu(enfant1, 0), Individu(enfant2, 0)};
}

// mutation d'un individu
Individu mutation(Individu parent) {
    static random_device rd; // Générateur aléatoire (mieux que rand)
    static mt19937 gen(rd());

    int size = parent.itineraire.size();
    uniform_int_distribution<int> dist(1, size - 1); // Éviter les extrémités

    int k = dist(gen);
    int l = dist(gen);

    while (k == l) { // S'assurer que k et l sont différents
        l = dist(gen);
    }

    Individu enfant = parent;
    swap(enfant.itineraire[k], enfant.itineraire[l]); // Échange des deux villes

    return enfant;
}

// sélection des reproducteurs

// Population selection_reproducteurs(const Population& adultes, enum modes_selection_reproducteurs mode_choisi = ROULETTE){
//     Population reproducteurs;
//     if(mode_choisi == ROULETTE){
//         auto iterateur = adultes.composition.begin();
//         double S = 0;
//         while(iterateur != adultes.composition.end()){
//             S = S + (*iterateur).adaptation;
//             iterateur++;
//             //cout<<S<<endl;
//         }
//         while(reproducteurs.composition.size()<adultes.composition.size()){
//             srand(time(0));
//             int r = rand()%(int)S;
//             int somme_cumulee=0;
//             iterateur = adultes.composition.begin();
//             while(iterateur != adultes.composition.end()){
//                 somme_cumulee=somme_cumulee+(*iterateur).adaptation;
//                 if(somme_cumulee>=r){
//                     break;
//                 }
//                 iterateur++;
                
//             }
//             reproducteurs.composition.push_back(*iterateur);
//         }
//     }
//     // Les trois autres modes de sélection des reproducteurs pourront être implémentés plus tard
//     return reproducteurs;
// }

Population selection_reproducteurs(const Population& adultes, enum modes_selection_reproducteurs mode_choisi) {
    Population reproducteurs;
    if (mode_choisi == ROULETTE) {
        double S = 0;
        for (const auto& individu : adultes.composition) {
            S += individu.adaptation;
        }
        
        if (S <= 0.0000001) {
            // Si la somme est trop petite, sélectionner aléatoirement
            while (reproducteurs.composition.size() < adultes.composition.size()) {
                int idx = rand() % adultes.composition.size();
                reproducteurs.composition.push_back(adultes.composition[idx]);
            }
            return reproducteurs;
        }
        
        // Sélection par roulette normale
        while (reproducteurs.composition.size() < adultes.composition.size()) {
            double r = (rand() / (double)RAND_MAX) * S;  // Utiliser un double pour éviter modulo 0
            double somme_cumulee = 0;
            
            for (const auto& individu : adultes.composition) {
                somme_cumulee += individu.adaptation;
                if (somme_cumulee >= r) {
                    reproducteurs.composition.push_back(individu);
                    break;
                }
            }
        }
    }
    return reproducteurs;
}


//sélection des composition qui vont survivre 

Population selection_population_finale(const Population& parents, const Population& enfants, int nombre_parents_survivants, enum modes_selection_pop_finale mode_choisi = ELITISME){
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


// Algorithme génétique principal
void algorithme_genetique(int max_generation, int taille_population, int nombre_villes,
    vector<vector<double>> matrice_des_distances, double frequence_mutation,
    int nombre_parents_survivants, int max_stagnation_generations) {

if (nombre_villes == 1) {  // ✅ Cas où il n'y a qu'une seule ville → solution unique
cout << "Solution optimale trouvée immédiatement : [0]" << endl;
cout << "Coût total : 0" << endl;
return;
}

Population P;
P.initialiser(taille_population, nombre_villes);
P.evaluer(matrice_des_distances);

double previousBestFitness = P.majorant().adaptation;
int stagnationCount = 0;
int i = 0;

while (i < max_generation) {
cout << "Générations " << i << " :" << distance_parcours(P.majorant(),matrice_des_distances) << endl;
Population parents = selection_reproducteurs(P, ROULETTE);
Population enfants;

while (enfants.composition.size() < taille_population) {
Individu maman = parents.composition[rand() % parents.composition.size()];
Individu papa = parents.composition[rand() % parents.composition.size()];
auto [enfant1, enfant2] = hybridation(maman, papa);
enfants.composition.push_back(enfant1);
enfants.composition.push_back(enfant2);
}

int j = 0;
while (j < enfants.composition.size() * frequence_mutation) {
int index = rand() % enfants.composition.size();
enfants.composition[index] = mutation(enfants.composition[index]);
j++;
}

P = selection_population_finale(parents, enfants, nombre_parents_survivants);
P.evaluer(matrice_des_distances);

double currentBestFitness = P.majorant().adaptation;
if (abs(currentBestFitness - previousBestFitness) <= 1e-6) {
stagnationCount++;
} else {
stagnationCount = 0;
}

if (stagnationCount >= max_stagnation_generations) {
cout << "Critère d'arrêt atteint : stagnation du fitness après " << stagnationCount << " générations." << endl;
break;
}

previousBestFitness = currentBestFitness;
i++;
}

P.majorant().afficher();
cout << "Coût total : " << distance_parcours(P.majorant(), matrice_des_distances) << endl;
cout << "Solution trouvée en " << i << " générations" << endl;
}