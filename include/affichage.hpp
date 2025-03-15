#ifndef AFFICHAGE_HPP
#define AFFICHAGE_HPP

#include <iostream>
#include <string>

// Structure pour une ville
struct Ville {
    float x, y;
    std::string nom;
};

void drawLineWithArrow(sf::RenderWindow&, sf::Vector2f, sf::Vector2f);

void afficherCarte(const std::vector<Ville>&, const std::vector<int>&, const std::vector<std::vector<int>>&);

#endif