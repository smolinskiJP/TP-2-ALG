#include "TreeSelector.hpp"

void Result::update(Point a, Point b, Point c, double p){
    if(p == INF) return;

    //Ordenando os novos indices
    int id[3] = {a.index, b.index, c.index};
    std::sort(id, id + 3);

    bool firstLexicographical = (
        (id[0] < this->t1) || 
        (id[0] == this->t1 && id[1] < this->t2) || 
        (id[0] == this->t1 && id[1] == this->t2 && id[2] < this->t3)
    );
    
    if(p < this->perim || (firstLexicographical && std::abs(p - this->perim) < 1e-9)){
        this->perim = p;
        this->t1 = id[0];
        this->t2 = id[1];
        this->t3 = id[2];
    }

}

TreeSelector::TreeSelector(int z) : _z(z){
    this->_trees = std::vector<Point>(z);

    Point p;
    //Pega os pontos
    for(int i = 0; i < z; i++){
        p.index = i + 1;
        std::cin >> p.x >> p.y;
        this->_trees[i] = p;
    }
}

TreeSelector::~TreeSelector(){}

Result TreeSelector::smallestPerim(std::vector<Point>& Px, std::vector<Point>& Py, int l, int r){
    int size = r - l + 1;
    Result result;

    //Caso base (Tamanho ate 5)
    if(size <= 5){
        for(int i = l; i <= r; i++){
            for(int j = i + 1; j <= r; j++){
                for(int k = j + 1; k <= r; k++){
                    double p = perimeter(Px[i], Px[j], Px[k]);
                    if(p <= result.perim) result.update(Px[i], Px[j], Px[k], p);
                }
            }
        }
        return result;
    }

    //Divisao: Divide o vetor das arvores (ordenadas em X) no meio e acha os menores perimetros em cada parte
    int mid = l + (size / 2);
    Point median = Px[mid];

    std::vector<Point> PyLeft, PyRight;

    for(Point p : Py){
        if(p.x < median.x) PyLeft.push_back(p);
        else if(p.x > median.x) PyRight.push_back(p);
        else{
            if(PyLeft.size() < (size_t)(mid - l + 1)) PyLeft.push_back(p);
            else PyRight.push_back(p);
        }
    }

    Result leftResult = smallestPerim(Px, PyLeft, l, mid);
    Result rightResult = smallestPerim(Px, PyRight, mid + 1, r);

    //Pega o menor perimetro entre as duas partes
    bool leftFirstLexic = (
        (leftResult.t1 < rightResult.t1) || 
        (leftResult.t1 == rightResult.t1 && leftResult.t2 < rightResult.t2) || 
        (leftResult.t1 == rightResult.t1 && leftResult.t2 == rightResult.t2 && leftResult.t3 < rightResult.t3)
    );

    if(leftResult.perim < rightResult.perim) result = leftResult;
    else if(leftResult.perim > rightResult.perim) result = rightResult;
    else if(leftFirstLexic) result = leftResult;
    else result = rightResult;

    //Conquista: Resta comparar com os trios que "cruzam" as duas divisoes, ou seja, que tem arvores antes e depois do limiar de X
    double perim = result.perim;

    //Agora devemos lidar com o caso de triangulos que cruzam o X mediano. Ou seja, que tem 2 pontos de um lado ou de outro
    //Sabemos o melhor perimetro ate agora, fica evidente que qualquer ponto a uma distancia do X mediano de mais de (perim / 2) nao vai participar desse triangulo
    //Entao devemos limitar o range em que os pontos serao comparados
    
    //Seleciona em Py, os que estao no "range"
    std::vector<Point> rangeTrees;
    for(Point p : Py) if(p.x - median.x < perim / 2.0) rangeTrees.push_back(p);
    
    //Verificar os triangulos dentro do range
    for(size_t i = 0; i < rangeTrees.size(); i++){
        for(size_t j = i + 1; j < rangeTrees.size(); j++){
            //Se a distancia entre 2 pontos ja for maior do que "range" pela metade, ja deve ser descartado
            if(rangeTrees[j].y - rangeTrees[i].y >= perim / 2.0) break;
            for(size_t k = j + 1; k < rangeTrees.size(); k++){
                if(rangeTrees[k].y - rangeTrees[i].y >= perim / 2.0) break;
                double p = perimeter(rangeTrees[i], rangeTrees[j], rangeTrees[k]);
                result.update(rangeTrees[i], rangeTrees[j], rangeTrees[k], p);
                perim = result.perim;
            }
        }
    }

    return result;
}

void TreeSelector::Run(){
    if(this->_z < 3) return;

    //Ordena as arvores em relacao a cordenada no X.
    std::sort(this->_trees.begin(), this->_trees.end(), [](const Point& a, const Point& b){
        return a.x < b.x;
    });

    //Ordena por Y previamente tambem. Isso diminui o custo do passo futuro de orndenar por Y cada subvetor da recursao
    //A ordenacao por Y foi feita para que se a diferenca vertical entre 2 pontos for maior do que metade do menor perimetro encontrado, nenhum "menor triangulo" vai ser formado com essa reta
    //Ordenado, para cada ponto, no momento em que a distancia vertical for maior do que metade do perimetro, nenhum proximo ponto tera distancia vertical menor.
    std::vector<Point> Py = this->_trees;
    std::sort(Py.begin(), Py.end(), [](const Point& a, const Point& b){
        return a.y < b.y;
    });

    //Primeira chamada para a divisao e conquista
    this->_resultado =  smallestPerim(this->_trees, Py, 0, this->_z - 1);
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Parte 2: " << this->_resultado.perim << " " << this->_resultado.t1 << " " << this->_resultado.t2 << " " << this->_resultado.t3 << "\n";
}

//Calculo de perimetro
double TreeSelector::perimeter(Point a, Point b, Point c){
    double d1 = dist(a, b), d2 = dist(b, c), d3 = dist(c, a);

    //Verifica colineariedade. Se os 3 pontos estao na mesma reta, a soma da distancia entre os 2 extremos e o intermediario tem que ser igual a distancia dos dois extremos 
    double epsilon = 1e-9; //Para evitar erros de float

    //Pega a maior distancia e a soma das menores
    double dMax = d1, dSum = d2 + d3;
    if(d2 > dMax){
        dMax = d2;
        dSum = d1 + d3;
    }
    if(d3 > dMax){
        dMax = d3;
        dSum = d1 + d2;
    }

    //Verifica a colinearidade. Se for colinear coloca o valor maximo de double no perimetro, para nao ser escolhido
    if(dSum - dMax < epsilon) return INF;

    return d1 + d2 + d3;
}

//Calculo de distancia
double TreeSelector::dist(Point a, Point b){
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}