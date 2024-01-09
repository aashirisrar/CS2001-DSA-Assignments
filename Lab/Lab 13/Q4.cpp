#include <iostream>
#include <queue>

using namespace std;

class graph
{
    int vertices;
    int **adjList;
    int maxvertices = 100;

public:
    graph(int V)
    {
        vertices = V;
        adjList = new int *[V];
        for (int i = 0; i < V; ++i)
        {
            adjList[i] = new int[V];
            for (int j = 0; j < V; ++j)
            {
                adjList[i][j] = 0; // Initialize all entries to 0
            }
        }
    }

    ~graph()
    {
        for (int i = 0; i < vertices; ++i)
        {
            delete[] adjList[i];
        }
        delete[] adjList;
    }

    void addEdge(int v, int w)
    {
        adjList[v][w] = 1;
        adjList[w][v] = 1; // For undirected graphs
    }

    void BFS(int start)
    {
        bool *visited = new bool[vertices];
        for (int i = 0; i < vertices; ++i)
        {
            visited[i] = false;
        }

        queue<int> bfsQueue;

        visited[start] = true;
        bfsQueue.push(start);

        cout << "BFS Traversal: ";

        while (!bfsQueue.empty())
        {
            int current = bfsQueue.front();
            bfsQueue.pop();

            cout << current << " ";

            for (int i = 0; i < vertices; ++i)
            {
                if (adjList[current][i] && !visited[i])
                {
                    visited[i] = true;
                    bfsQueue.push(i);
                }
            }
        }

        delete[] visited;
        cout << endl;
    }

    void printConnectedComponents()
    {
        bool *visited = new bool[vertices];
        for (int i = 0; i < vertices; ++i)
        {
            visited[i] = false;
        }

        int components = 0;

        for (int i = 0; i < vertices; ++i)
        {
            if (!visited[i])
            {
                BFS(i);
                components++;
            }
        }

        cout << "Number of connected components: " << components << endl;

        delete[] visited;
    }
};

int main()
{

    graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(3, 4);
    g.addEdge(5, 5);

    g.printConnectedComponents();

    return 0;
}