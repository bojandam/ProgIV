#include<iostream>
#include<vector>


//class NetworkGraph : public Graph {}
template<typename edge_weight_type = int>
class Graph {
protected:


    int n_vertices;
    bool directional;
    bool weighted;
    edge_weight_type default_edge_weight;

public:
    virtual int solveEdmondKarp() = 0;
    virtual int solveFordFulkerson() = 0;

    virtual void add_edge(int pFrom, int pTo) = 0;
    virtual void add_edge(int pFrom, int pTo, edge_weight_type weight) = 0;
    virtual void add_vertex() = 0;

    virtual void print() = 0;


    Graph(int n_vertices = 0, bool directional = true, bool weighted = false, edge_weight_type default_edge_weight = 1) :n_vertices(n_vertices), directional(directional), weighted(weighted), default_edge_weight(default_edge_weight) {};

};

template<typename edge_weight_type = int>
class MatrixGraph : public Graph<edge_weight_type> {
public:


    std::vector<std::vector<edge_weight_type>> matrix;

    MatrixGraph(int n_vertices = 0, bool directional = true, bool weighted = false, edge_weight_type default_edge_weight = 1) : Graph<edge_weight_type>(n_vertices, directional, weighted, default_edge_weight), matrix(n_vertices, std::vector<edge_weight_type>(n_vertices, 0)) {};
    void add_edge(int pFrom, int pTo, edge_weight_type weight) {
        matrix[pFrom][pTo] = weight;
        if (!this->directional)
            matrix[pTo][pFrom] = weight;
    }
    void add_edge(int pFrom, int pTo) { add_edge(pFrom, pTo, this->default_edge_weight); }
    void add_vertex() {
        this->n_vertices++;
        for (std::vector<edge_weight_type> vec : matrix)
            vec.push_back(0);

        matrix.push_back(std::vector<edge_weight_type>(this->n_vertices, 0));
    }
    void print() {
        for (int i = 0; i < this->n_vertices; i++) {
            for (int j = 0; j < this->n_vertices; j++) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    int solveEdmondKarp() {}
    int solveFordFulkerson() {}

};


int main() {

    int n, m; std::cin >> n >> m;

    MatrixGraph<> grf(n);
    for (int i = 0; i < m; i++) {
        int f, t, w;
        std::cin >> f >> t >> w;
        grf.add_edge(f, t, w);
    }
    grf.print();


}