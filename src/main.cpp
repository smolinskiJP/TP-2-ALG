#include <iostream>
#include "Wall.hpp"

#define SUCESSO 0

int main(){

    //Parte 1
    int n;
    std::cin >> n;

    Wall part1 = Wall(n);
    part1.Run();

    //Parte 2

    return SUCESSO;
}