#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <functional>
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
 