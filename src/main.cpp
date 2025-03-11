#include <iostream>
#include "brut.cpp"
#include "genetique.cpp"



int main()
{
    std::cout << "Hello world!" << std::endl;
    vector<vector<double>> Adj = input("input.txt");
    algorithme_genetique(5,20,3,Adj,0.1);
    return 0;
}
