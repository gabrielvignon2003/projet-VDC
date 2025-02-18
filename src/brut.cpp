#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
using namespace std;

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
    std::vector<double> dist;
    while (fichier >> mot) { // Lire mot par mot
        std::istringstream iss(mot);
        int nombre;
        if (iss >> nombre) {
            std::cout << "Nombre détecté : " << nombre << std::endl;
            dist.push_back(nombre);
        } else {
            std::cout << "Texte détecté : " << mot << std::endl;
        }
    }
    std::vector<std::vector<double>> Adj;
    for (int i=0;dist.size()/3;i++){
        std::vector<double> ligne;
        for (int j=0;j<dist.size();j++){
            if (j%3==0){
                ligne.push_back(distance(i+1,i+2,j+1,j+2));
            }
        }
        Adj.push_back(ligne);

    }
    std::cout << distance(1,1,2,3) << std::endl;
    fichier.close();
    return 0;
}

std::vector<double> resol(std::vector<std::vector<double>> Adj, int depart){
    int dim=sqrt(Adj.size());
    double min=0;
    

}