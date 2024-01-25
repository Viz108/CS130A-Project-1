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
    int componentNumber; 
}; 

void explore(int coordIndex, int componentType, int componentNumber, int numRows, int numCol, vector<coord> &list)
{
    if(list.at(coordIndex).value == componentType && !list.at(coordIndex).visited)
    {
        //Mark visited and component number
        list.at(coordIndex).componentNumber = componentNumber; 
        list.at(coordIndex).visited = true; 


        //Explore left node
        if(list.at(coordIndex).x > 0)
        {
            explore(list.at(coordIndex).y * numCol + (list.at(coordIndex).x-1), componentType, componentNumber, numRows, numCol, list); 
        }
        //Explore right node
        if(list.at(coordIndex).x < numCol-1)
        {
            explore(list.at(coordIndex).y * numCol + (list.at(coordIndex).x+1), componentType, componentNumber, numRows, numCol, list); 
        }
        //Explore above node
        if(list.at(coordIndex).y > 0)
        {
            explore((list.at(coordIndex).y-1) * numCol + list.at(coordIndex).x, componentType, componentNumber, numRows, numCol, list); 
        }
        //Explore below node
        if(list.at(coordIndex).y < numRows-1)
        {
            explore((list.at(coordIndex).y+1) * numCol + list.at(coordIndex).x, componentType, componentNumber, numRows, numCol, list); 
        }
    }
}

main()
{
    //Read in map and store in an adjacency list 

    vector<coord> adjacencyList; //Index of each node will be y*c+x

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
    }

    //Setup adjacencyList
    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++)
        {
            coord newCoord; 
            newCoord.x = j; 
            newCoord.y = i; 
            newCoord.value = strings.at(i).at(j)-48; 
            newCoord.visited = false; 
            adjacencyList.push_back(newCoord); 
        }
    }    

    //Decompose into components using DFS
    int currComponentNumber = 1;
    for(int i = 0; i < adjacencyList.size(); i++)
    {
        if(adjacencyList.at(i).visited == false)
        {
            cout << "Exploration call " << i << endl; 
            explore(i, adjacencyList.at(i).value, currComponentNumber, r, c, adjacencyList); 
            currComponentNumber++; 
        }
    }


}