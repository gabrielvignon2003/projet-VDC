#include <iostream>
#include "traitement_input.hpp"
#include <string>
#include "brut.hpp"
#include "genetique.hpp"
#include <chrono> 
#include <vector>
#include "aff.hpp"
//#include "affichage.hpp"

bool valider_matrice_distances(const vector<vector<double>>& matrice) {
    for (int i = 0; i < matrice.size(); i++) {
        for (int j = 0; j < matrice[i].size(); j++) {
            if (i != j && matrice[i][j] <= 0) { // Bloque les zéros et valeurs négatives
                cerr << "ERREUR: Distance invalide entre " << i << " et " << j << endl;
                return false;
            }
        }
    }
    return true;
}

//input.txt : 94 villes
//input2.txt : 6 villes, bien pour comparaison avec la force brute
//input3.txt : 11 villes

int main(){
    string input="./src/input3.txt";
    int taille_population = 200;
    int max_generation = 3000;
    double frequence_mutation = 0.03;
    int nombre_parents_survivants=100;
    int max_stagnation_generations=10;

    vector<vector<double>> adj = input_coordonnees(input);
    int nombre_villes= adj.size();
    cout<<"Chargement de la matrice des distances : OK"<<endl;
    if (!valider_matrice_distances(adj)) {
        cerr << "Matrice des distances corrompue !" << endl;
        return 1;
    }
    cout << "-----FORCE BRUTE-----" <<endl;
    auto start_brut = std::chrono::high_resolution_clock::now();
    tspBrut(adj);
    auto end_brut = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_brut = end_brut - start_brut;

    cout << "Temps algo Brut : " << duration_brut.count() << " secondes" << endl << endl;

    cout <<"-----GENETIQUE-----" <<endl;
    auto start_gen = std::chrono::high_resolution_clock::now();
    algorithme_genetique(max_generation, taille_population, nombre_villes, adj, frequence_mutation, nombre_parents_survivants, max_stagnation_generations);
    auto end_gen = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_gen = end_gen - start_gen;

    cout << "Temps algo génétique : " << duration_gen.count() << " secondes" << std::endl << endl;

    // Affichage du graphe

    // Initialisation de la fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Graphe avec poids");
    window.setFramerateLimit(60);

    vector<Sommet> sommets(nombre_villes);


    // Placer les sommets
    placerSommets(sommets, nombre_villes);

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Effacer la fenêtre avec un fond blanc
        window.clear(sf::Color::White);

        // Dessiner le graphe
        dessinerAretes(window, sommets, adj);
        dessinerSommets(window, sommets);

        // Afficher le contenu de la fenêtre
        window.display();
    }


    // Création des données pour traçage des graphiques sur matlab
    cout << "-----Création des données pour traçage des graphiques-----" << endl;
    cout << "1°) Evolution du nb d'éxécutions en fct du nb de villes : Force Brute" << endl;
    std::string tableau[16]={"./src/1_villes.txt","./src/2_villes.txt","./src/3_villes.txt", "./src/4_villes.txt", "./src/5_villes.txt", "./src/6_villes.txt","./src/7_villes.txt","./src/8_villes.txt","./src/9_villes.txt","./src/10_villes.txt", "./src/15_villes.txt", "./src/20_villes.txt", "./src/30_villes.txt", "./src/40_villes.txt", "./src/50_villes.txt", "./src/60_villes.txt"};
    vector<vector<double>> adj_test=input_coordonnees(tableau[15]);
    algorithme_genetique(max_generation, taille_population, adj_test.size(), adj_test, frequence_mutation, nombre_parents_survivants, max_stagnation_generations);
    /*
    for (int j=4;j<16;j++){
        adj_test=input_coordonnees(tableau[j]);
        if (j<10){
        auto start_brut = std::chrono::high_resolution_clock::now();
        tspBrut(adj_test);
        auto end_brut = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_brut = end_brut - start_brut;
        cout << "Temps algo Brut pour " << tableau[j] << " : " << duration_brut.count() << " secondes" << endl;
        
        auto start = std::chrono::high_resolution_clock::now();
        algorithme_genetique(max_generation, taille_population, adj_test.size(), adj_test, frequence_mutation, nombre_parents_survivants, max_stagnation_generations);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        cout << "Temps algo génétique pour " << tableau[j] << " : " << duration.count() << " secondes" << endl;
        
        }
        else {
            auto start = std::chrono::high_resolution_clock::now();
            algorithme_genetique(max_generation, taille_population, adj_test.size(), adj_test, frequence_mutation, nombre_parents_survivants, max_stagnation_generations);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            cout << "Temps algo génétique pour " << tableau[j] << " : " << duration.count() << " secondes" << endl;
    
        }


        
        
        
    }
    */
    
    /*
    for (int j=0;j<16;j++){
        adj_test=input_coordonnees(tableau[j]);
        int nb_villes = adj_test.size();
        auto start_gen = std::chrono::high_resolution_clock::now();
        algorithme_genetique(max_generation, taille_population, nb_villes, adj_test, frequence_mutation, nombre_parents_survivants, max_stagnation_generations);
        auto end_gen = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_gen = end_gen - start_gen;
        cout << "Temps algo génétique pour " << tableau[j] << " : " << duration_gen.count() << " secondes" << endl;
    }
    */




    return 0;
}
