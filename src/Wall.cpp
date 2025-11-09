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

    //Vetor que para cada ponto representa o maior triangulo retangulo que pode ser feito a esquerda do ponto
    std::vector<int> leftTriangle(this->_n);

    //Vetor que para cada ponto representa o maior triangulo retangulo que pode ser feito a direita do ponto
    std::vector<int> rightTriangle(this->_n);

    //O ponto mais a esquerda vai ser  iniciado como 1, pois vai ser o maior tamanho do triangulo a esquerda (tamanho maximo da pilha = 1)
    leftTriangle[0] = 1;
    
    //O ponto mais a direita vai ser iniciado como 1, pois vai ser o maior tamanho do triangulo a direita (tamanho maximo da pilha = 1)
    rightTriangle[this->_n - 1] = 1;

    for(int i = 1; i < this->_n; i++) {
        //Para cada pilha, a altura do triangulo a esquerda por padrao vai ser a do triangulo a esquerda da pilha a esquerda mais 1.
        //Caso a altura da pilha nao seja maior ou igual a esse valor, a propria altura da pilha vai ser o limitante do traingulo
        leftTriangle[i] = min(leftTriangle[i - 1] + 1, this->_heights[i]);

        //Uma logica semelhante mas invertida a de cima vale para a pilha a direita
        rightTriangle[this->_n - (i + 1)] = min(rightTriangle[this->_n - i] + 1, this->_heights[this->_n - (i + 1)]);
    }

    //Inicia com a menor altura sendo 0. Ja que nao ter pilhas vai ser como ter um triangulo de tamanho 0
    int maxHeight = 0;
    //Apos isso, para cada pilha verificamos qual o maior triangulo que pode ser gerado com ela, sendo esse o menor entre seus dois triangulos retangulos laterais
    //Se esse valor for a maior altura encontrada ate agora, a maior altura vai ser atualizada
    for(int i = 0; i < this->_n; i++) maxHeight = max(maxHeight, min(leftTriangle[i], rightTriangle[i]));

    //Saida como pede o enunciado
    std::cout << "Parte 1: " << maxHeight << "\n";
}

int Wall::min(int a, int b){
    return (a < b) ? a : b;
}

int Wall::max(int a, int b){
    return (a > b) ? a : b;
}