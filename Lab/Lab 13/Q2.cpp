#include <iostream>
#include <stack>

using namespace std;

class graph
{
    int vertices;
    int **adjMatrix;
    int maxverteices = 100;

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

    ~graph()
    {
        for (int i = 0; i < vertices; ++i)
        {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }

    void addEdge(int v, int w)
    {
        adjMatrix[v][w] = 1;
    }

    void topologicalSort(int v, bool visited[], stack<int> &orderStack)
    {
        visited[v] = true;

        for (int i = 0; i < vertices; ++i)
        {
            if (adjMatrix[v][i] == 1 && !visited[i])
            {
                topologicalSort(i, visited, orderStack);
            }
        }

        orderStack.push(v);
    }

    void topologicalSort()
    {
        stack<int> orderStack;
        bool *visited = new bool[vertices];

        for (int i = 0; i < vertices; ++i)
        {
            visited[i] = false;
        }

        for (int i = 0; i < vertices; ++i)
        {
            if (!visited[i])
            {
                topologicalSort(i, visited, orderStack);
            }
        }

        cout << "Topological Order: ";
        while (!orderStack.empty())
        {
            cout << orderStack.top() << " ";
            orderStack.pop();
        }

        delete[] visited;
    }
};

int main()
{

    graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    g.topologicalSort();

    return 0;
}