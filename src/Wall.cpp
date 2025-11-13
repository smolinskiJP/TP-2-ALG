#include "Wall.hpp"

Wall::Wall(int n) : _n(n){
    this->_heights = std::vector<int>(n);

    int height;
    //Pega as alturas
    for(int i = 0; i < n; i++){
        std::cin >> height;
        this->_heights[i] = height;
    }
}

Wall::~Wall(){}

void Wall::Run(){

    //O ponto mais a esquerda vai ser  iniciado como 1, pois vai ser o maior tamanho do triangulo a esquerda (tamanho maximo da pilha = 1)
    this->_heights[0] = 1;

    for(int i = 1; i < this->_n; i++) {
        //Para cada pilha, a altura do triangulo a esquerda por padrao vai ser a do triangulo a esquerda da pilha a esquerda mais 1.
        //Caso a altura da pilha nao seja maior ou igual a esse valor, a propria altura da pilha vai ser o limitante do traingulo
        this->_heights[i] = min(this->_heights[i - 1] + 1, this->_heights[i]);
    }

    //O ponto mais a direita vai ter altura maxima 1 tambem
    this->_heights[this->_n - 1] = 1;

    //Inicia com a menor altura sendo 1, ja que os extremos nao serao verificados na proxima etapa (por terem maximo de tamanho 1)
    int maxHeight = 1;
    for(int i = this->_n - 2; i >= 1; i--){
        this->_heights[i] = min(this->_heights[i + 1] + 1, this->_heights[i]);
        maxHeight = max(maxHeight, this->_heights[i]);
    }

    //Saida como pede o enunciado
    std::cout << "Parte 1: " << maxHeight << "\n";
}

int Wall::min(int a, int b){
    return (a < b) ? a : b;
}

int Wall::max(int a, int b){
    return (a > b) ? a : b;
}