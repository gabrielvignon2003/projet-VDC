#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <functional>
#include <limits>
using namespace std;

class Individu{
    public:
        vector<int> villes;
        int depart;
        vector<int> itineraire;
        double adaptation;

        //constructeur paramétrique
        Individu(vector<int> villes_, int depart_, vector<int> itineraire_,double adaptation_):
        villes(villes_),depart(depart_),itineraire(itineraire_),adaptation(adaptation_){};
        
        //constructeur par copie
        Individu(const Individu& autre):villes(autre.villes),depart(autre.depart),
        itineraire(autre.itineraire),adaptation(autre.adaptation){};
};

class Population{
    public:
        int taille;
        vector<Individu> composition;
};

Individu generate_indiv(std::vector<std::vector<double>> Adj,int n){
    int ville = 0;
    int i = rand()%n;
    vector<int> vide;
    double inf = numeric_limits<double>;
    Individu I(vide,0,vide,inf);
    while(Adj[0][i] != 0 ){
        i = rand()%n;
    }
    I.itineraire[0] = i;
    vector<int> marque(n, 0);
    marque[i] = 1;
    vector<int> vec(n, 1);
    int pos = i;
    int j = rand()%n;
    while(marque != vec){
        while(Adj[pos][j] != 0 ){
            j = rand()%n;
        }    
        marque[j]=1;
        I.itineraire.push_back(j);
        pos = j;
        j = rand()%n;
    }
    return I;
}

Population generate_pop(int n){
    Population P;
    for(int i =0;i<n;i++){
        P.composition[i] = generate_indiv();
    }
    return P
}

pair<Individu,Individu> hybridation(Individu& papa, Individu& maman){
    Individu enfant_pm(maman);
    Individu enfant_mp(maman);
    srand(time(0));
    int separation=rand()%enfant_pm.itineraire.size()+1;
    int i=0;
    while(i<separation){
        enfant_pm.itineraire[i]=papa.itineraire[i];
    }
    i=separation;
    while(i<enfant_pm.itineraire.size()){
        enfant_mp.itineraire[i]=papa.itineraire[i];
        i++;
    }

    pair<Individu,Individu> fratrie(enfant_pm,enfant_mp);

    return fratrie;
    
    
}



Individu mutation(Individu parent){
    srand(time(0));
    int k = 1 + rand() % (parent.itineraire.size()-2);
    int l = 1 + rand() % (parent.itineraire.size()-2);
    Individu enfant(parent);
    enfant.itineraire[l] = parent.itineraire[k];
    enfant.itineraire[l-1] = parent.itineraire[k+1];
    enfant.itineraire[k] = parent.itineraire[l];
    enfant.itineraire[k+1] = parent.itineraire[l-1];
    return enfant;
}


Population Reproduction(Population parent,const std::function<Population(Population)>& func,int q){ //l'entier q correspond au nombre d'individu de la population parent que l'on souhaite conserver
    Population enfant(parent);
    pair<Individu,Individu> Ptemp(parent.composition[0],parent.composition[0]);
    Population P2 = func(parent);
    int n = parent.taille;
    if(P2.taille <= n){
        for(int i = 0 ; i<P2.taille ; i++){
            enfant.composition[i]=P2.composition[i];
        }
        int i = P2.taille;
        while(i <= n -2){
            srand(time(0));
            Ptemp = hybridation(P2.composition[rand()%P2.taille],P2.composition[rand()%P2.taille]);
            enfant.composition[i]=Ptemp.first;
            enfant.composition[i+1]=Ptemp.second;
            i += 2;
        }
        while(i<n){
            enfant.composition[i]=mutation(P2.composition[rand()%P2.taille]);
            i++;
        }
    }
    else{
        cout<<"erreur 05"<<endl;
    }
    return enfant;
}



int main(){
    return 0;
}
 