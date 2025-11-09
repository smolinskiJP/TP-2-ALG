#ifndef WALL_HPP
#define WALL_HPP

#include <vector>
#include <iostream>

class Wall{
    private:
        int _n;
        std::vector<int> _heights;

        int max(int a, int b);
        int min(int a, int b);
    public:
        Wall(int n);
        ~Wall();
        void Run();
};

#endif