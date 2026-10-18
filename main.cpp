#include <iostream>
#include <string>
using namespace std;

const int N = 12;
const int INF = 99999;

// Location names
string locationName[N] = {
    "Main Gate",
    "College Chowk",
    "Bus Stand",
    "Railway Station",
    "Civil Hospital",
    "City Hospital",
    "Fire Station",
    "Police Station",
    "Market",
    "Residential Area",
    "Industrial Area",
    "University Road"
};
string locationType[N] = {
    "Normal", "Normal", "Normal", "Normal",
    "Hospital", "Hospital", "Fire Station",
    "Police Station", "Normal", "Normal",
    "Normal", "Normal"
};
int road[N][N];
int status[N][N];
void makeMap()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
            {
                road[i][j] = 0;
            }
            else
            {
                road[i][j] = INF;
            }

            status[i][j] = 0;
        }
    }
}
void addRoad(int a, int b, int distance)
{
    road[a][b] = distance;
    road[b][a] = distance;
}
void createRoads()
{
    addRoad(0, 1, 4);
    addRoad(1, 2, 3);
    addRoad(2, 3, 5);
    addRoad(3, 4, 4);
    addRoad(4, 5, 3);
    addRoad(5, 6, 6);
    addRoad(6, 7, 2);
    addRoad(7, 8, 4);
    addRoad(8, 9, 3);
    addRoad(9, 10, 5);
    addRoad(10, 11, 4);
    addRoad(11, 0, 7);
    addRoad(0, 4, 8);
    addRoad(1, 5, 6);
    addRoad(2, 6, 7);
    addRoad(3, 7, 5);
    addRoad(4, 8, 4);
    addRoad(5, 9, 6);
    addRoad(6, 10, 3);
    addRoad(7, 11, 5);
}
void showMap()
{
    cout << "\n========== CITY LOCATIONS ==========\n";

    for (int i = 0; i < N; i++)
    {
        cout << "ID: " << i
             << " | Name: " << locationName[i]
             << " | Type: " << locationType[i] << endl;
    }
    cout << "\n========== CITY ROADS ==========\n";
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (road[i][j] != INF)
            {
                count++;
                cout << count << ". "
                     << locationName[i] << " <-> "
                     << locationName[j]
                     << " | Distance: "
                     << road[i][j] << " km" << endl;
            }
        }
    }
    cout << "\nTotal Locations: " << N;
    cout << "\nTotal Roads: " << count << endl;
}
void showDistanceMatrix()
{
    cout << "\n========== DISTANCE MATRIX ==========\n";
    cout << "INF means no direct road.\n\n";
    cout << "ID\t";
    for (int i = 0; i < N; i++)
    {
        cout << i << "\t";
    }
    cout << endl;
    for (int i = 0; i < N; i++)
    {
        cout << i << "\t";
        for (int j = 0; j < N; j++)
        {
            if (road[i][j] == INF)
            {
                cout << "INF\t";
            }
            else
            {
                cout << road[i][j] << "\t";
            }
        }
        cout << endl;
    }
}
void showStatusMatrix()
{
    cout << "\n========== ROAD STATUS MATRIX ==========\n";
    cout << "0 = Normal Road\n";
    cout << "-- = No Direct Road\n\n";
    cout << "ID\t";
    for (int i = 0; i < N; i++)
    {
        cout << i << "\t";
    }
    cout << endl;
    for (int i = 0; i < N; i++)
    {
        cout << i << "\t";
        for (int j = 0; j < N; j++)
        {
            if (i == j || road[i][j] == INF)
            {
                cout << "--\t";
            }
            else
            {
                cout << status[i][j] << "\t";
            }
        }
        cout << endl;
    }
}
void testCityMap()
{
    int count = 0;
    bool correct = true;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (road[i][j] != INF)
            {
                count++;
            }
        }
    }
    if (count == 20)
    {
        cout << "\nPASS: Total 20 roads found.\n";
    }
    else
    {
        cout << "\nFAIL: Road count is incorrect.\n";
        correct = false;
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (road[i][j] != road[j][i])
            {
                correct = false;
            }
        }
    }
    if (correct)
    {
        cout << "PASS: Two-way roads are correct.\n";
    }
    else
    {
        cout << "FAIL: Check the road matrix.\n";
    }
    for (int i = 0; i < N; i++)
    {
        if (road[i][i] != 0)
        {
            cout << "FAIL: Diagonal value is incorrect.\n";
            return;
        }
    }
    cout << "PASS: All diagonal values are zero.\n";
}
int main()
{
    int choice;
    makeMap();
    createRoads();
    do
    {
        cout << "  SMART EMERGENCY RESCUE SYSTEM\n";
        cout << "        CITY MAP MODULE\n";
        cout << "====================================\n";
        cout << "1. View City Map\n";
        cout << "2. View Distance Matrix\n";
        cout << "3. View Road Status Matrix\n";
        cout << "4. Test City Map\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
                showMap();
                break;
            case 2:
                showDistanceMatrix();
                break;
            case 3:
                showStatusMatrix();
                break;
            case 4:
                testCityMap();
                break;
            case 5:
                cout << "Exiting program\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);
    return 0;
}

