
#include <iostream>
#include <string>
using namespace std;

const int N = 12;

// Arrays defined by other members
extern int road[N][N];
extern int status[N][N];
extern string locationName[N];
extern string locationType[N];
extern int beds[N];

// BFS arrays
int dist[N];
int parent[N];
int visited[N];

// Road status:
// 0 = Clear
// 1 = Traffic
// 2 = Accident
// 3 = Construction


// 1. BFS using an array-based queue
void bfs(int source)
{
    int queue[N];
    int front = 0;
    int rear = 0;

    for (int i = 0; i < N; i++)
    {
        dist[i] = -1;
        parent[i] = -1;
        visited[i] = 0;
    }

    queue[rear] = source;
    rear++;

    visited[source] = 1;
    dist[source] = 0;

    while (front < rear)
    {
        int current = queue[front];
        front++;

        for (int next = 0; next < N; next++)
        {
            if (road[current][next] > 0 &&
                visited[next] == 0)
            {
                // Ignore accident and construction roads
                if (status[current][next] == 2 ||
                    status[current][next] == 3)
                {
                    continue;
                }

                visited[next] = 1;
                dist[next] = dist[current] + 1;
                parent[next] = current;

                queue[rear] = next;
                rear++;
            }
        }
    }
}


// 2. Display the route
void showRoute(int destination)
{
    if (dist[destination] == -1)
    {
        cout << "\nNo route available!\n";
        return;
    }

    int path[N];
    int count = 0;
    int current = destination;

    // Store route from destination to source
    while (current != -1)
    {
        path[count] = current;
        count++;

        current = parent[current];
    }

    cout << "\nRoute: ";

    // Display route from source to destination
    for (int i = count - 1; i >= 0; i--)
    {
        cout << locationName[path[i]];

        if (i > 0)
        {
            cout << " -> ";
        }
    }

    cout << "\nNumber of roads: "
         << dist[destination] << endl;

    // Check traffic on the selected route
    bool trafficFound = false;

    for (int i = count - 1; i > 0; i--)
    {
        int a = path[i];
        int b = path[i - 1];

        if (status[a][b] == 1)
        {
            trafficFound = true;
        }
    }

    if (trafficFound)
    {
        cout << "Warning: Traffic exists on this route.\n";
    }
}


// 3. Bubble Sort facilities by route length
void bubbleSort(int facilities[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (dist[facilities[j]] >
                dist[facilities[j + 1]])
            {
                int temp = facilities[j];

                facilities[j] = facilities[j + 1];
                facilities[j + 1] = temp;
            }
        }
    }
}


// 4. Search for a suitable emergency facility
int findFacility(int source, int helpType)
{
    string requiredType;

    if (helpType == 1)
    {
        requiredType = "Hospital";
    }
    else if (helpType == 2)
    {
        requiredType = "Fire Station";
    }
    else
    {
        requiredType = "Police Station";
    }

    // Find routes from the emergency location
    bfs(source);

    int facilities[N];
    int count = 0;

    // Search all reachable locations
    for (int i = 0; i < N; i++)
    {
        if (dist[i] == -1)
        {
            continue;
        }

        if (locationType[i] == requiredType)
        {
            // Hospital must have an available bed
            if (helpType == 1 && beds[i] <= 0)
            {
                continue;
            }

            facilities[count] = i;
            count++;
        }
    }

    if (count == 0)
    {
        cout << "\nNo suitable facility is available "
             << "through an open route.\n";

        return -1;
    }

    // Sort facilities from nearest to farthest
    bubbleSort(facilities, count);

    cout << "\nSuitable facilities (nearest first):\n";

    for (int i = 0; i < count; i++)
    {
        int id = facilities[i];

        cout << i + 1 << ". "
             << locationName[id]
             << " | Number of roads: "
             << dist[id];

        if (helpType == 1)
        {
            cout << " | Available beds: " << beds[id];
        }

        cout << endl;
    }

    // Select the nearest suitable facility
    int nearest = facilities[0];

    cout << "\nNearest suitable facility: "
         << locationName[nearest] << endl;

    showRoute(nearest);

    return nearest;
}


// 5. Report an emergency
void reportEmergency()
{
    int source;
    int helpType;

    cout << "\n===== REPORT EMERGENCY =====\n";

    cout << "\nAvailable locations:\n";

    for (int i = 0; i < N; i++)
    {
        cout << i + 1 << ". "
             << locationName[i] << endl;
    }

    cout << "\nEnter emergency location ID (1-12): ";
    cin >> source;

    if (cin.fail() || source < 1 || source > N)
    {
        cout << "Invalid location ID!\n";

        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    // Convert ID into array index
    source--;

    cout << "\nRequired help:\n";
    cout << "1. Hospital\n";
    cout << "2. Fire Station\n";
    cout << "3. Police Station\n";

    cout << "Enter your choice: ";
    cin >> helpType;

    if (cin.fail() || helpType < 1 || helpType > 3)
    {
        cout << "Invalid help type!\n";

        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    findFacility(source, helpType);
}
