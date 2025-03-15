#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <sstream>
#include "../include/affichage.hpp"



// Fonction pour dessiner une ligne avec une flèche au milieu
void drawLineWithArrow(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end) {
    // Dessiner la ligne
    sf::Vertex line[] = {
        sf::Vertex(start, sf::Color::Blue), // Ligne bleue
        sf::Vertex(end, sf::Color::Blue)
    };

    // Calculer le point médian de la ligne
    sf::Vector2f middle = (start + end) / 2.0f;

    // Calculer les propriétés de la flèche
    float angle = atan2(end.y - start.y, end.x - start.x); // Angle de la ligne
    float arrowLength = 10.0f; // Longueur de la flèche
    float arrowAngle = 30.0f; // Angle de la flèche (en degrés)

    // Calculer les points des deux côtés de la flèche au niveau du point médian
    sf::Vector2f arrowPoint1 = middle - sf::Vector2f(cos(angle - arrowAngle * M_PI / 180) * arrowLength,
                                                     sin(angle - arrowAngle * M_PI / 180) * arrowLength);
    sf::Vector2f arrowPoint2 = middle - sf::Vector2f(cos(angle + arrowAngle * M_PI / 180) * arrowLength,
                                                     sin(angle + arrowAngle * M_PI / 180) * arrowLength);

    // Afficher la ligne
    window.draw(line, 2, sf::Lines);

    // Dessiner la flèche
    sf::ConvexShape arrow(3); // Flèche est un triangle
    arrow.setPoint(0, middle); // Point principal de la flèche (au milieu de la ligne)
    arrow.setPoint(1, arrowPoint1); // Premier côté
    arrow.setPoint(2, arrowPoint2); // Deuxième côté
    arrow.setFillColor(sf::Color::Black); // Couleur de la flèche

    // Afficher la flèche
    window.draw(arrow);
}

// Fonction pour dessiner les villes et le chemin optimal
void afficherCarte(const std::vector<Ville>& villes, const std::vector<int>& chemin, const std::vector<std::vector<int>>& couts) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Voyageur de Commerce");
    sf::Font font;
    
    // Essayer de charger la police
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur de chargement de la police" << std::endl;
    }

    // Calcul du coût total
    int coutTotal = 0;
    for (size_t i = 0; i < chemin.size() - 1; ++i) {
        coutTotal += couts[chemin[i]][chemin[i + 1]];
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Dessiner le chemin optimal avec des flèches au milieu
        for (size_t i = 0; i < chemin.size() - 1; ++i) {
            sf::Vector2f start(villes[chemin[i]].x, villes[chemin[i]].y);
            sf::Vector2f end(villes[chemin[i+1]].x, villes[chemin[i+1]].y);
            drawLineWithArrow(window, start, end);

            // Calculer le point médian pour afficher le coût
            sf::Vector2f middle = (start + end) / 2.0f;

            // Créer le texte du coût
            sf::Text coutText;
            coutText.setFont(font);
            coutText.setCharacterSize(14);
            coutText.setFillColor(sf::Color::Black);

            // Afficher le coût entre les deux villes
            std::stringstream ss;
            ss << couts[chemin[i]][chemin[i + 1]];
            coutText.setString(ss.str());
            coutText.setPosition(middle.x - 15, middle.y - 15); // Ajuster la position si nécessaire

            // Afficher le texte
            window.draw(coutText);
        }

        // Dessiner les villes et leurs noms
        for (size_t i = 0; i < villes.size(); i++) {
            sf::CircleShape point(5);
            point.setFillColor(sf::Color::Red);
            point.setPosition(villes[i].x - 2.5, villes[i].y - 2.5);
            window.draw(point);

            sf::Text text;
            if (font.getInfo().family.empty()) {
                // Si la police n'a pas pu être chargée, utiliser un texte par défaut
                text.setString("Police non trouvée");
            } else {
                // Sinon, afficher le nom de la ville
                text.setFont(font);
                text.setCharacterSize(14);
                text.setFillColor(sf::Color::Black);
                text.setString(villes[i].nom);
            }
            text.setPosition(villes[i].x + 5, villes[i].y - 10);
            window.draw(text);
        }

        // Ajouter "Départ" et "Arrivée"
        sf::Text departText;
        departText.setFont(font);
        departText.setCharacterSize(16);
        departText.setFillColor(sf::Color::Green);
        departText.setString("Start");
        departText.setPosition(villes[chemin.front()].x + 10, villes[chemin.front()].y + 10);
        window.draw(departText);

        // Afficher le coût total
        sf::Text coutText;
        coutText.setFont(font);
        coutText.setCharacterSize(16);
        coutText.setFillColor(sf::Color::Black);
        std::stringstream ss;
        ss << "Coût total: " << coutTotal;
        coutText.setString(ss.str());
        coutText.setPosition(10, 10);
        window.draw(coutText);

        window.display();
    }
}

int main() {
    // Exemple : Liste de villes avec noms
    std::vector<Ville> villes = {
        {100, 150, "A"}, {200, 80, "B"}, {300, 200, "C"}, {400, 100, "D"}, {500, 300, "E"}, {600, 250, "F"}
    };

    // Matrice des coûts entre les villes (par exemple, coût entre la ville 0 et la ville 1)
    std::vector<std::vector<int>> couts = {
        {0, 10, 15, 20, 25, 30},
        {10, 0, 35, 25, 30, 20},
        {15, 35, 0, 30, 10, 15},
        {20, 25, 30, 0, 15, 25},
        {25, 30, 10, 15, 0, 20},
        {30, 20, 15, 25, 20, 0}
    };

    // Chemin optimal donné par un algorithme de TSP
    std::vector<int> chemin = {0, 1, 3, 2, 4, 5, 0}; // Retour au point de départ

    afficherCarte(villes, chemin, couts);

    return 0;
}





