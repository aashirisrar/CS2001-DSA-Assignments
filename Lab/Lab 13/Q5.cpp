#include <iostream>
using namespace std;

const int maxedges = 100;
class Edge
{
public:
    int src, dest, weight;
    int maxvertices = 100;

    Edge() {}
    Edge(int s, int d, int w)
    {
        src = s;
        dest = d;
        weight = w;
    }
};

class Graph
{
    int vertices;

    Edge edges[maxedges];

public:
    Graph(int V)
    {
        vertices = 0;
    }

    void addEdge(int src, int dest, int weight)
    {
        edges[vertices++] = Edge(src, dest, weight);
    }

    int find(int parent[], int i)
    {
        if (parent[i] == -1)
            return i;
        return find(parent, parent[i]);
    }

    void Union(int parent[], int x, int y)
    {
        int xRoot = find(parent, x);
        int yRoot = find(parent, y);
        parent[xRoot] = yRoot;
    }

    // Simple implementation of selection sort
    void sortEdges()
    {
        for (int i = 0; i < vertices - 1; ++i)
        {
            int minIndex = i;
            for (int j = i + 1; j < vertices; ++j)
            {
                if (edges[j].weight < edges[minIndex].weight)
                {
                    minIndex = j;
                }
            }
            swap(edges[i], edges[minIndex]);
        }
    }

    void kruskalMST()
    {
        sortEdges();

        int *parent = new int[vertices];
        fill(parent, parent + vertices, -1);

        cout << "Edges of Minimum Spanning Tree (MST):" << endl;

        for (int i = 0; i < vertices; ++i)
        {
            int x = find(parent, edges[i].src);
            int y = find(parent, edges[i].dest);

            if (x != y)
            {
                cout << edges[i].src << " -- " << edges[i].dest << " Weight: " << edges[i].weight << endl;
                Union(parent, x, y);
            }
        }

        delete[] parent;
    }
};

int main()
{
    // Create a sample weighted undirected graph
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 2, 15);

    // Find and print the Minimum Spanning Tree (MST) using Kruskal's algorithm
    g.kruskalMST();

    return 0;
}