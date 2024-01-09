#include <iostream>
using namespace std;

class graph
{
    int vertices;
    int **adjMatrix;

public:
    graph(int V)
    {
        vertices = V;
        adjMatrix = new int *[V];
        for (int i = 0; i < V; ++i)
        {
            adjMatrix[i] = new int[V];
            for (int j = 0; j < V; ++j)
            {
                adjMatrix[i][j] = 0; // Initialize all entries to 0
            }
        }
    }

    void addEdge(int v, int w)
    {
        adjMatrix[v][w] = 1;
        adjMatrix[w][v] = 1; // For undirected graphs
    }

    void DFS(int v, bool *visited)
    {
        visited[v] = true;
        for (int i = 0; i < vertices; ++i)
        {
            if (adjMatrix[v][i] == 1 && !visited[i])
            {
                DFS(i, visited);
            }
        }
    }

    int countcomponents()
    {
        bool *visited = new bool[vertices];
        for (int i = 0; i < vertices; ++i)
        {
            visited[i] = false;
        }

        int count = 0;

        for (int v = 0; v < vertices; ++v)
        {
            if (!visited[v])
            {
                DFS(v, visited);
                count++;
            }
        }

        delete[] visited;
        return count;
    }

    ~graph()
    {
        for (int i = 0; i < vertices; ++i)
        {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }
};

int main()
{

    graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(3, 4);
    g.addEdge(5, 5);

    int connectedComponents = g.countcomponents();

    cout << "Number of connected components: " << connectedComponents << endl;

    return 0;
}