#include <iostream>
#include "brut.cpp"
#include "genetique.cpp"



int main()
{
    std::cout << "Hello world!" << std::endl;
    vector<vector<double>> Adj = input();
    algorithme_genetique(5,20,3);
    return 0;
}
