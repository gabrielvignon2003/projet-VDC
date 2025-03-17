#ifndef AFF_HPP
#define AFF_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

// Constantes pour la taille de la fenêtre et le rayon des sommets
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int RADIUS = 20;

// Structure représentant un sommet dans le graphe
struct Sommet {
    int id;                // Identifiant du sommet
    sf::Vector2f position; // Position du sommet dans la fenêtre
};

// Déclaration des fonctions

// Fonction pour calculer la position des sommets sur le cercle
void placerSommets(std::vector<Sommet>& sommets, int nombre_sommets);

// Fonction pour dessiner les arêtes entre les sommets
// Elle dessine aussi les poids au milieu des arêtes
void dessinerAretes(sf::RenderWindow& window, std::vector<Sommet>& sommets, const std::vector<std::vector<double>>& matrice_adjacence);

// Fonction pour dessiner les sommets avec leurs numéros
void dessinerSommets(sf::RenderWindow& window, std::vector<Sommet>& sommets);

#endif // AFF_HPP

