#include<iostream>
#include<vector>
#include<queue>
#include<stack>


using std::vector;


class Graph {
protected:

    int n_vertices;
    bool directional;
    bool weighted;
    int default_edge_weight;


    int Network_bfs(int s, int t, vector<int> & parent, vector<vector<int>>adj, vector<vector<int>>capacity) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        std::queue<std::pair<int, int> >q;
        q.push({ s,__INT_MAX__ });

        while (!q.empty())
        {

            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (int next : adj[cur]) {
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
    int Network_dfs(int s, int t, vector<int> & parent, vector<vector<int>>adj, vector<vector<int>>capacity) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        std::stack<std::pair<int, int> >q;
        q.push({ s,__INT_MAX__ });

        while (!q.empty())
        {

            int cur = q.top().first;
            int flow = q.top().second;
            q.pop();

            for (int next : adj[cur]) {
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
    bool Level_bfs(int s, int t, vector<int> & level, vector<vector<int>>adj, vector<vector<int>> capacity) {

        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        std::queue<int>q;
        q.push(s);

        while (!q.empty())
        {
            int cur = q.front();
            q.pop();

            for (int next : adj[cur]) {
                if (level[next] == -1 && capacity[cur][next] != 0) {
                    level[next] = level[cur] + 1;
                    q.push(next);
                }
            }
        }
        return level[t] != -1;
    }
    int Dinic_dfs(int v, int t, vector<int> & level, vector<vector<int>> adj, vector<vector<int>> & capacity, int rez = 100000)
    {
        if (rez == 0) return 0;
        if (v == t)
            return rez;
        for (int next : adj[v]) {
            if (level[next] == level[v] + 1 && capacity[v][next] != 0) {
                int flow = Dinic_dfs(next, t, level, adj, capacity, std::min(rez, capacity[v][next]));
                if (flow != 0) {
                    capacity[v][next] -= flow;
                    capacity[next][v] += flow;
                    return flow;
                }
            }
        }
        return 0;

    }


    int EdmondKarp(int s, int t, vector<vector<int>> & adj, vector<vector<int>> & capacity) {
        int rez = 0, new_flow;
        vector<int> parents(n_vertices, -1);

        while (new_flow = Network_bfs(s, t, parents, adj, capacity)) {
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
    int FordFulkerson(int s, int t, vector<vector<int>> & adj, vector<vector<int>> & capacity) {
        int rez = 0, new_flow;
        vector<int> parents(n_vertices, -1);

        while (new_flow = Network_dfs(s, t, parents, adj, capacity)) {
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
    int Dinic(int s, int t, vector<vector<int>> & adj, vector<vector<int>> & capacity) {

        int rez_flow = 0, new_flow;
        vector<int> level(n_vertices, -1);

        while (Level_bfs(s, t, level, adj, capacity))
            while (new_flow = Dinic_dfs(s, t, level, adj, capacity))
                rez_flow += new_flow;

        return rez_flow;
    }

    vector<std::pair<int, int> > stCut(int s, int t, vector<vector<int>> & adj, vector<vector<int>> & capacity) {
        Dinic(s, t, adj, capacity);
        vector<int> level(n_vertices, -1);
        Level_bfs(s, t, level, adj, capacity);
        vector<std::pair<int, int> > cutEdges;
        for (int v = 0; v < n_vertices; v++) {
            if (level[v] != -1) {
                for (int u : adj[v]) {
                    if (level[u] == -1) {
                        cutEdges.push_back({ v,u });
                        std::cout << v << " -> " << u << ", ";
                    }
                }
            }
        }
        return cutEdges;

    }
public:
    virtual int solveEdmondKarp(int, int) = 0;
    virtual int solveFordFulkerson(int, int) = 0;
    virtual int solveDinic(int, int) = 0;
    virtual vector<std::pair<int, int> > solveSTCut(int, int) = 0;


    virtual void add_edge(int pFrom, int pTo) = 0;
    virtual void add_edge(int pFrom, int pTo, int weight) = 0;
    virtual void add_vertex() = 0;

    virtual void print() = 0;


    Graph(int n_vertices = 0, bool directional = true, bool weighted = false, int default_edge_weight = 1) :n_vertices(n_vertices), directional(directional), weighted(weighted), default_edge_weight(default_edge_weight) {};

};

class MatrixGraph : public Graph {
public:


    vector<vector<int>> matrix;
    vector<vector<int>> adjList;

    MatrixGraph(int n_vertices = 0, bool directional = true, bool weighted = false, int default_edge_weight = 1) : Graph(n_vertices, directional, weighted, default_edge_weight), matrix(n_vertices, vector<int>(n_vertices, 0)), adjList(n_vertices) {}

    void add_edge(int pFrom, int pTo, int weight) {
        matrix[pFrom][pTo] = weight;
        adjList[pFrom].push_back(pTo);

        if (!directional) {
            matrix[pTo][pFrom] = weight;
            adjList[pTo].push_back(pFrom);
        }
    }
    void add_edge(int pFrom, int pTo) { add_edge(pFrom, pTo, default_edge_weight); }
    void add_vertex() {
        n_vertices++;
        for (vector<int> & vec : matrix)
            vec.push_back(0);
        matrix.push_back(vector<int>(n_vertices, 0));
        adjList.push_back(vector<int>());
    }
    void print() {
        for (int i = 0; i < n_vertices; i++) {
            for (int j = 0; j < n_vertices; j++) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        for (int i = 0; i < n_vertices; i++) {
            for (int el : adjList[i]) {
                std::cout << el << " ";
            }
            std::cout << std::endl;
        }
    }
public:

    int solveEdmondKarp(int s = 0, int t = -1) {

        if (t == -1)t = n_vertices - 1;

        vector<vector<int>> capacity(matrix);

        return EdmondKarp(s, t, adjList, capacity);
    }

    int solveFordFulkerson(int s = 0, int t = -1) {

        if (t == -1)t = n_vertices - 1;

        vector<vector<int>> capacity(matrix);

        return FordFulkerson(s, t, adjList, capacity);
    }

    int solveDinic(int s = 0, int t = -1) {

        if (t == -1)t = n_vertices - 1;

        vector<vector<int>> capacity(matrix);

        return Dinic(s, t, adjList, capacity);
    }

    vector<std::pair<int, int> > solveSTCut(int s = 0, int t = -1) {

        if (t == -1)t = n_vertices - 1;

        vector<vector<int>> capacity(matrix);

        return stCut(s, t, adjList, capacity);
    }

};

class ListGraph : public Graph {
public:



    vector<vector<std::pair<int, int> >> adjList;

    ListGraph(int n_vertices = 0, bool directional = true, bool weighted = false, int default_edge_weight = 1) : Graph(n_vertices, directional, weighted, default_edge_weight), adjList(n_vertices) {}

    void add_edge(int pFrom, int pTo, int weight) {

        adjList[pFrom].push_back({ pTo,weight });

        if (!directional) {
            adjList[pTo].push_back({ pFrom,weight });
        }
    }
    void add_edge(int pFrom, int pTo) { add_edge(pFrom, pTo, default_edge_weight); }
    void add_vertex() {
        n_vertices++;
        adjList.push_back(vector<std::pair<int, int>>());
    }
    void print() {

        for (int i = 0; i < n_vertices; i++) {
            for (std::pair<int, int> el : adjList[i]) {
                std::cout << el.first << " " << el.second;
            }
            std::cout << std::endl;
        }
    }

private:
    vector<vector<int>> capacity;
    vector<vector<int>> temp_adj;

    void prepare_capacity() {
        capacity = vector<vector<int>>(n_vertices, vector<int>(n_vertices, 0));
        for (int i = 0; i < n_vertices; i++)
            for (std::pair<int, int> el : adjList[i])
                capacity[i][el.first] = el.second;
    }
    void prepare_temp_adj() {
        temp_adj = vector<vector<int>>(n_vertices);
        for (int i = 0; i < n_vertices; i++) {
            for (auto pr : adjList[i]) {
                temp_adj[i].push_back(pr.first);
            }
        }
    }

public:
    int solveEdmondKarp(int s = 0, int t = -1) {

        if (t == -1)t = n_vertices - 1;

        prepare_capacity();
        prepare_temp_adj();

        return EdmondKarp(s, t, temp_adj, capacity);
    }
    int solveFordFulkerson(int s = 0, int t = -1) {

        if (t == -1)t = n_vertices - 1;

        prepare_capacity();
        prepare_temp_adj();

        return FordFulkerson(s, t, temp_adj, capacity);
    }
    int solveDinic(int s = 0, int t = -1) {

        if (t == -1)t = n_vertices - 1;

        prepare_capacity();
        prepare_temp_adj();

        return Dinic(s, t, temp_adj, capacity);
    }
    vector<std::pair<int, int> > solveSTCut(int s = 0, int t = -1) {
        if (t == -1)t = n_vertices - 1;

        prepare_capacity();
        prepare_temp_adj();

        return stCut(s, t, temp_adj, capacity);
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
    std::cout << grf.solveDinic() << "\n";
    grf.solveSTCut(); std::cout << std::endl;
    std::cout << grf1.solveEdmondKarp() << " ";
    std::cout << grf1.solveFordFulkerson() << " ";
    std::cout << grf1.solveDinic() << "\n";
    grf1.solveSTCut(); std::cout << std::endl;

    return 0;
    /*

    4
    5
    0 1 3
    0 2 2
    1 2 5
    1 3 2
    2 3 3

    ans: 5

    6 9
    0 1 7
    0 4 4
    1 2 5
    1 3 3
    2 5 8
    3 2 3
    3 5 5
    4 1 3
    4 3 2

    ans: 10

    */



}
