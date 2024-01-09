#include <iostream>
#include <queue>

using namespace std;

const int maxstations = 26; // Assuming station names are single uppercase letters

class SubwaySystem
{
private:
    char adjacencyList[maxstations][maxstations];
    int stationDegrees[maxstations];

public:
    SubwaySystem()
    {
        for (int i = 0; i < maxstations; ++i)
        {
            stationDegrees[i] = 0;
            for (int j = 0; j < maxstations; ++j)
            {
                adjacencyList[i][j] = '\0';
            }
        }
    }

    void addEdge(char station1, char station2)
    {
        int index1 = station1 - 'A';
        int index2 = station2 - 'A';

        adjacencyList[index1][stationDegrees[index1]++] = station2;
        adjacencyList[index2][stationDegrees[index2]++] = station1; // For an undirected graph
    }

    int bfsCountStations(char start, char destination)
    {
        int startIdx = start - 'A';
        int destIdx = destination - 'A';

        bool visited[maxstations] = {false};
        queue<pair<int, int>> bfsQueue; // Pair of station index and distance

        bfsQueue.push({startIdx, 0});
        visited[startIdx] = true;

        while (!bfsQueue.empty())
        {
            int currentStationIdx = bfsQueue.front().first;
            int distance = bfsQueue.front().second;
            bfsQueue.pop();

            if (currentStationIdx == destIdx)
            {
                return distance;
            }

            for (int i = 0; i < stationDegrees[currentStationIdx]; ++i)
            {
                char neighbor = adjacencyList[currentStationIdx][i];
                int neighborIdx = neighbor - 'A';
                if (!visited[neighborIdx])
                {
                    bfsQueue.push({neighborIdx, distance + 1});
                    visited[neighborIdx] = true;
                }
            }
        }

        // If destination is not reachable from the start
        return -1;
    }
};

int main()
{
    SubwaySystem subway;

    subway.addEdge('A', 'B');
    subway.addEdge('B', 'C');
    subway.addEdge('B', 'D');
    subway.addEdge('C', 'E');
    subway.addEdge('D', 'E');
    subway.addEdge('E', 'F');

    char startStation = 'A';
    char destinationStation = 'C';

    int numberOfStations = subway.bfsCountStations(startStation, destinationStation);

    if (numberOfStations != -1)
    {
        cout << "Number of stations to travel from " << startStation << " to " << destinationStation << ": " << numberOfStations << endl;
    }
    else
    {
        cout << "Destination station is not reachable from the start station." << endl;
    }

    return 0;
}