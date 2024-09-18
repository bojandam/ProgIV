#include<iostream>
#include<vector>
#include<queue>
#include<stack>
//class NetworkGraph : public Graph {}

class Graph {
protected:

    int n_vertices;
    bool directional;
    bool weighted;
    int default_edge_weight;

public:
    virtual int solveEdmondKarp(int, int) = 0;
    virtual int solveFordFulkerson(int, int) = 0;

    virtual void add_edge(int pFrom, int pTo) = 0;
    virtual void add_edge(int pFrom, int pTo, int weight) = 0;
    virtual void add_vertex() = 0;

    virtual void print() = 0;


    Graph(int n_vertices = 0, bool directional = true, bool weighted = false, int default_edge_weight = 1) :n_vertices(n_vertices), directional(directional), weighted(weighted), default_edge_weight(default_edge_weight) {};

};

class MatrixGraph : public Graph {
public:


    std::vector<std::vector<int>> matrix;
    std::vector<std::vector<int>> adjList;

    MatrixGraph(int n_vertices = 0, bool directional = true, bool weighted = false, int default_edge_weight = 1) : Graph(n_vertices, directional, weighted, default_edge_weight), matrix(n_vertices, std::vector<int>(n_vertices, 0)), adjList(n_vertices) {}

    void add_edge(int pFrom, int pTo, int weight) {
        matrix[pFrom][pTo] = weight;
        adjList[pFrom].push_back(pTo);

        if (!this->directional) {
            matrix[pTo][pFrom] = weight;
            adjList[pTo].push_back(pFrom);
        }
    }
    void add_edge(int pFrom, int pTo) { add_edge(pFrom, pTo, this->default_edge_weight); }
    void add_vertex() {
        this->n_vertices++;
        for (std::vector<int> vec : matrix)
            vec.push_back(0);
        matrix.push_back(std::vector<int>(this->n_vertices, 0));
        adjList.push_back(std::vector<int>());
    }
    void print() {
        for (int i = 0; i < this->n_vertices; i++) {
            for (int j = 0; j < this->n_vertices; j++) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        for (int i = 0; i < this->n_vertices; i++) {
            for (int el : adjList[i]) {
                std::cout << el << " ";
            }
            std::cout << std::endl;
        }
    }
private:
    int Network_bfs(int s, int t, std::vector<int> & parent, std::vector<std::vector<int>>capacity) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        std::queue<std::pair<int, int> >q;
        q.push({ s,__INT_MAX__ });

        while (!q.empty())
        {

            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (int next : adjList[cur]) {
                if (parent[next] == -1 && capacity[cur][next] != 0) {
                    parent[next] = cur;
                    int new_flow = std::min(flow, capacity[cur][next]);
                    if (next == t)
                        return new_flow;
                    q.push({ next, new_flow });
                }
            }

        }
        return 0;
    }
    int Network_dfs(int s, int t, std::vector<int> & parent, std::vector<std::vector<int>>capacity) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        std::stack<std::pair<int, int> >q;
        q.push({ s,__INT_MAX__ });

        while (!q.empty())
        {

            int cur = q.top().first;
            int flow = q.top().second;
            q.pop();

            for (int next : adjList[cur]) {
                if (parent[next] == -1 && capacity[cur][next] != 0) {
                    parent[next] = cur;
                    int new_flow = std::min(flow, capacity[cur][next]);
                    if (next == t)
                        return new_flow;
                    q.push({ next, new_flow });
                }
            }

        }
        return 0;
    }
public:
    int solveEdmondKarp(int s = 0, int t = -1) {

        if (t == -1)t = this->n_vertices - 1;
        std::vector<std::vector<int>> capacity(matrix);
        int rez = 0, new_flow;
        std::vector<int> parents(this->n_vertices, -1);

        while (new_flow = Network_bfs(s, t, parents, capacity)) {
            rez += new_flow;
            int cur = t;
            while (cur != s)
            {
                int prev = parents[cur];
                capacity[prev][cur] -= new_flow;
                capacity[cur][prev] += new_flow;
                cur = prev;
            }
        }
        return rez;
    }

    int solveFordFulkerson(int s = 0, int t = -1) {

        if (t == -1)t = this->n_vertices - 1;
        std::vector<std::vector<int>> capacity(matrix);
        int rez = 0, new_flow;
        std::vector<int> parents(this->n_vertices, -1);

        while (new_flow = Network_dfs(s, t, parents, capacity)) {
            rez += new_flow;
            int cur = t;
            while (cur != s)
            {
                int prev = parents[cur];
                capacity[prev][cur] -= new_flow;
                capacity[cur][prev] += new_flow;
                cur = prev;
            }
        }
        return rez;
    }

};

class ListGraph : public Graph {
public:



    std::vector<std::vector<std::pair<int, int> >> adjList;

    ListGraph(int n_vertices = 0, bool directional = true, bool weighted = false, int default_edge_weight = 1) : Graph(n_vertices, directional, weighted, default_edge_weight), adjList(n_vertices) {}

    void add_edge(int pFrom, int pTo, int weight) {

        adjList[pFrom].push_back({ pTo,weight });

        if (!this->directional) {
            adjList[pTo].push_back({ pFrom,weight });
        }
    }
    void add_edge(int pFrom, int pTo) { add_edge(pFrom, pTo, this->default_edge_weight); }
    void add_vertex() {
        this->n_vertices++;
        adjList.push_back(std::vector<std::pair<int, int>>());
    }
    void print() {

        for (int i = 0; i < this->n_vertices; i++) {
            for (std::pair<int, int> el : adjList[i]) {
                std::cout << el.first << " " << el.second;
            }
            std::cout << std::endl;
        }
    }
private:
    int Network_bfs(int s, int t, std::vector<int> & parent, std::vector<std::vector<int>>capacity) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        std::queue<std::pair<int, int> >q;
        q.push({ s,__INT_MAX__ });

        while (!q.empty())
        {

            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (std::pair<int, int> el : adjList[cur]) {
                int next = el.first;
                if (parent[next] == -1 && capacity[cur][next] != 0) {
                    parent[next] = cur;
                    int new_flow = std::min(flow, capacity[cur][next]);
                    if (next == t)
                        return new_flow;
                    q.push({ next, new_flow });
                }
            }

        }
        return 0;
    }
    int Network_dfs(int s, int t, std::vector<int> & parent, std::vector<std::vector<int>>capacity) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        std::stack<std::pair<int, int> >q;
        q.push({ s,__INT_MAX__ });

        while (!q.empty())
        {

            int cur = q.top().first;
            int flow = q.top().second;
            q.pop();

            for (std::pair<int, int> el : adjList[cur]) {
                int next = el.first;
                if (parent[next] == -1 && capacity[cur][next] != 0) {
                    parent[next] = cur;
                    int new_flow = std::min(flow, capacity[cur][next]);
                    if (next == t)
                        return new_flow;
                    q.push({ next, new_flow });
                }
            }

        }
        return 0;
    }
public:
    int solveEdmondKarp(int s = 0, int t = -1) {

        if (t == -1)t = this->n_vertices - 1;
        std::vector<std::vector<int>> capacity(n_vertices, std::vector<int>(n_vertices, 0));
        for (int i = 0; i < n_vertices; i++)
            for (std::pair<int, int> el : adjList[i])
                capacity[i][el.first] = el.second;

        int rez = 0, new_flow;
        std::vector<int> parents(this->n_vertices, -1);

        while (new_flow = Network_bfs(s, t, parents, capacity)) {
            rez += new_flow;
            int cur = t;
            while (cur != s)
            {
                int prev = parents[cur];
                capacity[prev][cur] -= new_flow;
                capacity[cur][prev] += new_flow;
                cur = prev;
            }
        }
        return rez;
    }

    int solveFordFulkerson(int s = 0, int t = -1) {

        if (t == -1)t = this->n_vertices - 1;
        std::vector<std::vector<int>> capacity(n_vertices, std::vector<int>(n_vertices, 0));
        for (int i = 0; i < n_vertices; i++)
            for (std::pair<int, int> el : adjList[i])
                capacity[i][el.first] = el.second;

        int rez = 0, new_flow;
        std::vector<int> parents(this->n_vertices, -1);

        while (new_flow = Network_dfs(s, t, parents, capacity)) {
            rez += new_flow;
            int cur = t;
            while (cur != s)
            {
                int prev = parents[cur];
                capacity[prev][cur] -= new_flow;
                capacity[cur][prev] += new_flow;
                cur = prev;
            }
        }
        return rez;
    }

};

int main() {

    int n, m; std::cin >> n >> m;

    MatrixGraph grf(n);
    ListGraph grf1(n);
    for (int i = 0; i < m; i++) {
        int f, t, w;
        std::cin >> f >> t >> w;
        grf.add_edge(f, t, w);
        grf1.add_edge(f, t, w);
    }

    std::cout << grf.solveEdmondKarp() << " ";
    std::cout << grf.solveFordFulkerson() << " ";
    std::cout << grf1.solveEdmondKarp() << " ";
    std::cout << grf1.solveFordFulkerson();


    return 0;
}