#ifndef TREESELECTOR_HPP
#define TREESELECTOR_HPP

#include <vector>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <algorithm> //Apenas usando a funcao sort, como permitido

//Constante para representar o maior double possivel
const double INF = 1e308;

//Estrutura usada para combinar as informações de um ponto, coordenadas X, Y e index
struct Point{
    int index;
    int x;
    int y;
};

//Estrutura que combina as informacoes de um perimetro, o valor e os indices dos pontos
struct Result{
    double perim;
    int t1;
    int t2;
    int t3;

    //Iniciador padrao
    Result(){perim = INF; t1 = -1; t2 = -1; t3 = -1;}
    void update(Point a, Point b, Point c, double p);
};

class TreeSelector{
    private:
        int _z;
        std::vector<Point> _trees;
        Result _resultado;

        double perimeter(Point a, Point b, Point c);
        double dist(Point a, Point b);
        Result smallestPerim(std::vector<Point>& Px, int l, int r);
    public:
        TreeSelector(int z);
        ~TreeSelector();
        void Run();
};

#endif