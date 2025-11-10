#ifndef TREESELECTOR_HPP
#define TREESELECTOR_HPP

#include <vector>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <algorithm> //Apenas usando a funcao sort, como permitido

const double INF = 1e308;

struct Point{
    int index;
    int x;
    int y;
};

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
        void updateResult(Point a, Point b, Point c, double p);
    public:
        TreeSelector(int z);
        ~TreeSelector();
        void Run();
};

#endif