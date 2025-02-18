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
    std::ifstream fichier("input.txt");
    if (!fichier) {
        std::cerr << "Erreur lors de l'ouverture du fichier !" << std::endl;
        return 1;
    }
    std::string mot;
    std::vector<double> coordonnees;
    while (fichier >> mot) { // Lire mot par mot
        std::istringstream iss(mot);
        int nombre;
        if (iss >> nombre) {
            std::cout << "Nombre détecté : " << nombre << std::endl;
            coordonnees.push_back(nombre);
        } else {
            std::cout << "Texte détecté : " << mot << std::endl;
        }
    }
    vector<vector<double>> Adj;
    for (int i=0;i<coordonnees.size();i+=2){
        std::vector<double> ligne;
        for (int j=0;j<coordonnees.size();j+=2){
            cout<<coordonnees.size()<<endl;
            if (j%2==0){
                ligne.push_back(distance(coordonnees[i],coordonnees[i+1],coordonnees[j],coordonnees[j+1]));
            }
        }
        Adj.push_back(ligne);

    }
    
    std::cout << distance(1,1,2,3) << std::endl;


    for (int i=0; i<Adj.size(); i++) {
        for (int j = 0; j<Adj[i].size(); j++) {
            cout << "[" << Adj[i][j] << "]";
        }
        // Add a new line after every row
        cout << endl;
    }
    fichier.close();
    return 0;
}

std::vector<double> resol(std::vector<std::vector<double>> Adj, int depart){
    int dim=sqrt(Adj.size());
    double min=0;
    

}