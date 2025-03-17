#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int RADIUS = 20;

// Structure représentant un sommet
struct Sommet {
    int id;
    sf::Vector2f position;
};

// Fonction pour calculer la position des sommets
void placerSommets(vector<Sommet>& sommets, int nombre_sommets) {
    float angle_step = 2 * M_PI / nombre_sommets;
    for (int i = 0; i < nombre_sommets; ++i) {
        sommets[i].id = i;
        sommets[i].position = sf::Vector2f(WINDOW_WIDTH / 2 + cos(i * angle_step) * 200, 
                                           WINDOW_HEIGHT / 2 + sin(i * angle_step) * 200);
    }
}

// Fonction pour dessiner les arêtes entre les sommets et afficher les poids
void dessinerAretes(sf::RenderWindow& window, vector<Sommet>& sommets, const vector<vector<double>>& matrice_adjacence) {
    for (int i = 0; i < sommets.size(); ++i) {
        for (int j = i + 1; j < sommets.size(); ++j) {
            if (matrice_adjacence[i][j] != 0) {
                // Dessiner l'arête entre les deux sommets
                sf::Vertex line[] = {
                    sf::Vertex(sommets[i].position, sf::Color::Black),
                    sf::Vertex(sommets[j].position, sf::Color::Black)
                };
                window.draw(line, 2, sf::Lines);

                // Calculer le point médian de l'arête
                sf::Vector2f midPoint = (sommets[i].position + sommets[j].position) / 2.f;

                // Afficher le poids de l'arête au point médian
                sf::Font font;
                if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
                    cerr << "Erreur de chargement de la police" << endl;
                    return;
                }

                sf::Text text;
                text.setFont(font);
                text.setString(std::to_string(matrice_adjacence[i][j]));
                text.setCharacterSize(6);
                text.setFillColor(sf::Color::Black);
                text.setPosition(midPoint.x - 10, midPoint.y - 10); // Positionnement du texte au centre de l'arête
                window.draw(text);
            }
        }
    }
}

// Fonction pour dessiner les sommets avec leurs numéros
void dessinerSommets(sf::RenderWindow& window, vector<Sommet>& sommets) {
    for (const auto& sommet : sommets) {
        sf::CircleShape cercle(RADIUS);
        cercle.setPosition(sommet.position.x - RADIUS, sommet.position.y - RADIUS);
        cercle.setFillColor(sf::Color::Green);
        window.draw(cercle);

        // Numéro du sommet
        sf::Font font;
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
            cerr << "Erreur de chargement de la police" << endl;
            return;
        }
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(sommet.id));
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        text.setPosition(sommet.position.x - RADIUS / 2, sommet.position.y - RADIUS / 2);
        window.draw(text);
    }
}


