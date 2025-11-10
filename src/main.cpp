#include <iostream>
#include "Wall.hpp"
#include "TreeSelector.hpp"

#define SUCESSO 0

int main(){

    //Parte 1
    int n;
    std::cin >> n;

    Wall part1 = Wall(n);
    part1.Run();

    //Parte 2
    int z;
    std::cin >> z;

    TreeSelector part2 = TreeSelector(z);
    part2.Run();

    return SUCESSO;
}