#include <iostream>
#include <climits>

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

    void addEdge(int v, int w, int weight)
    {
        adjList[v][w] = weight;
        adjList[w][v] = weight; // For undirected graphs
    }
    void DFS(int v, bool *visited)
    {
        visited[v] = true;
        for (int i = 0; i < vertices; ++i)
        {
            if (adjList[v][i] && !visited[i])
            {
                DFS(i, visited);
            }
        }
    }

    int countConnectedComponents()
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

    int shortestPath(int start, int end)
    {
        int *dist = new int[vertices];
        for (int i = 0; i < vertices; ++i)
        {
            dist[i] = INT_MAX;
        }

        dist[start] = 0;

        bool *processed = new bool[vertices];
        for (int i = 0; i < vertices; ++i)
        {
            processed[i] = false;
        }

        for (int i = 0; i < vertices - 1; ++i)
        {
            int u = minDistance(dist, processed);
            processed[u] = true;

            for (int v = 0; v < vertices; ++v)
            {
                if (!processed[v] && adjList[u][v] && dist[u] != INT_MAX && dist[u] + adjList[u][v] < dist[v])
                {
                    dist[v] = dist[u] + adjList[u][v];
                }
            }
        }

        int result = dist[end];

        delete[] dist;
        delete[] processed;

        return result;
    }

    int minDistance(int dist[], bool processed[])
    {
        int minDist = INT_MAX;
        int minIndex = -1;

        for (int v = 0; v < vertices; ++v)
        {
            if (!processed[v] && dist[v] <= minDist)
            {
                minDist = dist[v];
                minIndex = v;
            }
        }

        return minIndex;
    }
};

int main()
{
    graph g(6);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 3, 3);
    g.addEdge(2, 4, 5);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 5, 2);

    int connectedComponents = g.countConnectedComponents();
    cout << "Number of connected components: " << connectedComponents << endl;

    // Find the shortest path between vertices 1 and 4
    int shortestPathLength = g.shortestPath(1, 4);
    cout << "Shortest path length between vertices 1 and 4: " << shortestPathLength << endl;

    return 0;
}