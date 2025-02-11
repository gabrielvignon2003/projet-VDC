#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>


double distance(double i1, double j1, double i2, double j2){
    return sqrt((i1-i2)*(i1-i2)+(j1-j2)*(j1-j2));
}

int main() {
    std::ifstream fichier("monfichier.txt");
    if (!fichier) {
        std::cerr << "Erreur lors de l'ouverture du fichier !" << std::endl;
        return 1;
    }
    std::string mot;
    std::vector<double> distance;
    while (fichier >> mot) { // Lire mot par mot
        std::istringstream iss(mot);
        int nombre;
        if (iss >> nombre) {
            std::cout << "Nombre détecté : " << nombre << std::endl;
            distance.push_back(iss);
        } else {
            std::cout << "Texte détecté : " << mot << std::endl;
        }
    }
    std::vector<std::vector<double>> Adj;
    for (int i=0;i/distance.size();i++){
        std::vector<double> ligne;
        for (int i=0;i/distance.size();i++)
        ligne.push_back()

    }
    std::cout << distance(1,1,2,3) << std::endl;
    fichier.close();
    return 0;
}