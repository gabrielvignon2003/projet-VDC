#include <iostream>
#include <vector>
using namespace std;

class Individu{
    public: 
        Individu(const Individu& autre):villes(autre.villes),depart(autre.depart),
        itineraire(autre.itineraire),adaptation(autre.adaptation){};
    private:
        vector<int> villes;
        int depart;
        vector<int> itineraire;
        double adaptation;
};

class Population{
    private:
        int taille;
        vector<vector<int>> composition;
};

Individu hybridation(Individu papa, Individu maman){
    Individu enfant(&maman);
}

int main(){
    return 0;
}
