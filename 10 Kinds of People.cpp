#include <iostream>
#include <string>
#include <vector>

using namespace std; 

struct coord
{
    int x; 
    int y; 
    int value; 
    vector<int> neighbors;  //stores indexes of neighbors
    bool visited = false; 
}; 

bool explore(int x, int y, int rowLength, int search_x, int search_y, int pathValue, vector<coord> &list)
{
    //cout << "Searching " << x << ", " << y << endl; 
    int startIndex = (y*rowLength)+x; 
    if(list.at(startIndex).visited == true)
    {
        cout << "Already searched" << endl; 
        return false; 
    }
    else
    {
        list.at(startIndex).visited = true; 
    }

    if(list.at(startIndex).value != pathValue)
    {
        // cout << "Wrong value" << endl; 
        // cout << "Path value: " << pathValue << endl; 
        // cout << "Actual value: " << list.at(startIndex).value << endl; 
        return false; //Invalid region, return false
    }
    else if(search_x == x && search_y == y)
    {   
        //cout << "Target reached" << endl; 
        return true; //Found target, return true
    }
    else if(list.at(startIndex).neighbors.size() == 0)
    {
        return false; //Path ends, return false
    }
    else
    {
        bool searchFlag = false; 
        for(int i = 0; i < list.at(startIndex).neighbors.size(); i++)
        {
            cout << "Searching neighbor" << i << endl; 
            if(explore(list.at(list.at(startIndex).neighbors.at(i)).x, list.at(list.at(startIndex).neighbors.at(i)).y, rowLength, search_x, search_y, pathValue, list))
            {
                searchFlag = true;
                break; 
            }
        }
        return searchFlag; 
    }
}

main()
{
    //Read in map and store in an adjacency list 

    vector<coord> adjacencyList; 

    int r, c; 
    cin >> r; 
    cin >> c; 

    vector<string> strings; 
    for(int i = 0; i < r; i++)
    {
        //cout << "Row " << i << endl; 
        string newString; 
        cin >> newString; 
        strings.push_back(newString);  

        for(int j = 0; j < c; j++)
        {
            //cout << "Col " << j << endl; 
            //add entry for current location
            coord newCoords; 
            newCoords.x = j; 
            newCoords.y = i; 
            newCoords.value = strings.at(i).at(j)-48; 

            //check previous location (to the left) for edge
            if(j > 0)
            {
                if((strings.at(i).at(j-1)-48) == newCoords.value)
                {
                    newCoords.neighbors.push_back(adjacencyList.size()-1); 
                    adjacencyList.at(adjacencyList.size()-1).neighbors.push_back(adjacencyList.size());
                }
            }
            if(i > 0)
            {
                if((strings.at(i-1).at(j)-48) == newCoords.value)
                {
                    newCoords.neighbors.push_back(adjacencyList.size()-c); 
                    adjacencyList.at(adjacencyList.size()-c).neighbors.push_back(adjacencyList.size()); 
                }
            }
            adjacencyList.push_back(newCoords); 
        }
    }

    //Perform search using DFS

    int n; 
    cin >> n; 
    
    for(int i = 0; i < n; i++)
    {
        int r1, c1, r2, c2; 
        cin >> r1; 
        cin >> c1; 
        cin >> r2; 
        cin >> c2; 

        vector<coord> searchList = adjacencyList; 
        bool isPath = explore(c1-1, r1-1, c, c2-1, r2-1, adjacencyList.at(((r1-1)*c)+(c1-1)).value, searchList); 
        if(isPath)
        {
            if(adjacencyList.at(((r1-1)*c)+(c1-1)).value == 0)
            {
                cout << "binary" << endl; 
            }
            else
            {
                cout << "decimal" << endl; 
            }
        }
        else
        {
            cout << "neither" << endl; 
        }
    }

    // for(int i = 0; i < adjacencyList.size(); i++)
    // {
    //     cout << "Entry x: " << adjacencyList.at(i).x << " y: " << adjacencyList.at(i).y << endl; 
    //     cout << "   Neighbors: " <<endl; 
    //     for(int j = 0; j < adjacencyList.at(i).neighbors.size(); j++)
    //     {
    //         cout << "  Entry x: " << adjacencyList.at(adjacencyList.at(i).neighbors.at(j)).x << " y: " << adjacencyList.at(adjacencyList.at(i).neighbors.at(j)).y << endl; 
    //     }
    //     cout << endl; 
    // }
}