#include <iostream>
#include "Wall.hpp"
#include "TreeSelector.hpp"

#define SUCESSO 0

int main(){

    //Parte 1

    //Pega quantidade de pilhas
    int n;
    std::cin >> n;

    //Inicia e roda algoritmo
    Wall part1 = Wall(n);
    part1.Run();

    //Parte 2

    //Pega quantidade de pontos
    int z;
    std::cin >> z;

    //Inicia e roda o algoritmo
    TreeSelector part2 = TreeSelector(z);
    part2.Run();

    return SUCESSO;
}