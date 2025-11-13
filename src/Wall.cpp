#include "Wall.hpp"

//Construtor padrao, recebe o numero de pilhas e pega elas da entrada
Wall::Wall(int n) : _n(n){
    this->_heights = std::vector<int>(n);

    int height;
    //Pega as alturas
    for(int i = 0; i < n; i++){
        std::cin >> height;
        this->_heights[i] = height;
    }
}

//Destrutor padrao
Wall::~Wall(){}

//Roda o algoritmo de encontrar maior altura
void Wall::Run(){
    //Se nao tiver pilhas, apenas retorna
    if(this->_n == 0) return;

    //O ponto mais a esquerda vai ser  iniciado como 1, pois vai ser o maior tamanho do triangulo a esquerda (tamanho maximo da pilha = 1)
    this->_heights[0] = 1;
    //O ponto mais a direita vai ter altura maxima 1 tambem, pelo mesmo motivo
    this->_heights[this->_n - 1] = 1;

    //Acha o menor numero entre o valor limitado pelo vizinho a esquerda e a propria altura
    for(int i = 1; i < this->_n; i++) {
        //Para cada pilha, a altura do triangulo a esquerda por padrao vai ser a do triangulo a esquerda da pilha a esquerda mais 1.
        //Caso a altura da pilha nao seja maior ou igual a esse valor, a propria altura da pilha vai ser o limitante do triangulo
        this->_heights[i] = min(this->_heights[i - 1] + 1, this->_heights[i]);
    }

    //Inicia com a menor altura sendo 1, ja que os extremos nao serao verificados na proxima etapa (por terem maximo de tamanho 1)
    int maxHeight = 1;

    //Acha o menor numero entre o limitante atual e o valor limitado pelo vizinho a direita. Ao mesmo tempo pega o maior valor que encontrar entre as diferentes iteracoes
    for(int i = this->_n - 2; i >= 1; i--){
        this->_heights[i] = min(this->_heights[i + 1] + 1, this->_heights[i]);
        maxHeight = max(maxHeight, this->_heights[i]);
    }

    //Saida como pede o enunciado
    std::cout << "Parte 1: " << maxHeight << "\n";
}

//Retorna o minimo entre 2 inteiros
int Wall::min(int a, int b){
    return (a < b) ? a : b;
}

//Retorna o maximo entre 2 inteiros
int Wall::max(int a, int b){
    return (a > b) ? a : b;
}