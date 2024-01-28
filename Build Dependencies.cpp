#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <queue>

using namespace std; 


struct fileInfo
{
    vector<string> dependents = vector<string>(); 
    bool visited = false; 
}; 

void searchDependencies(string searchFile, map<string, fileInfo> &list, vector<string> &printQueue)
{   
    list.at(searchFile).visited = true; 
    for(int i = 0; i < list.at(searchFile).dependents.size(); i++)
    {
        if(!list.at(list.at(searchFile).dependents.at(i)).visited)
        {
            searchDependencies(list.at(searchFile).dependents.at(i), list, printQueue);  
        }
    }
    printQueue.push_back(searchFile); 
}

main()
{
    map<string, fileInfo> adjacencyList; 

    int n; 
    cin >> n; 

    for(int i = 0; i <= n; i++)
    {
        string currLine;
        string newDepend;
        getline(cin, currLine);

        string currFile = currLine.substr(0, currLine.find(":")); 
        currLine.erase(0, currLine.find(":") + 1); 

        //If current file isn't in list, add it

        adjacencyList.insert(pair{currFile, fileInfo()}); 

        while(currLine.length() != 0)
        { 
            //Read in dependencies 
            if(currLine.at(0) == ' ')
            {
                currLine.erase(0, 1);
            }
 
            if(currLine.find(" ") != currLine.npos) //Search for next dependency
            {
                newDepend = currLine.substr(0, currLine.find(" "));
                currLine.erase(0, currLine.find(" ") + 1);
            }
            else
            {
                newDepend = currLine; //EOL, rest of string is the next file
                currLine = ""; 
            }

            //Add current file to the dependencies dependent list
            if(adjacencyList.find(newDepend) != adjacencyList.end())
            {
                adjacencyList[newDepend].dependents.push_back(currFile); 
            }
            else
            {
                adjacencyList.insert(pair{newDepend, fileInfo()}); 
                adjacencyList[newDepend].dependents.push_back(currFile); 
            }    
        }
    }

    // for(const auto &p : adjacencyList)
    // {
    //     cout << p.first << ":" << endl; 
    //     for(int i = 0; i < p.second.size(); i++)
    //     {
    //         cout << p.second[i] << endl; 
    //     }
    //     cout << endl;
    // }

    //Run DFS from search file and print dependencies in order
    string searchFile; 
    cin >> searchFile; 
    vector<string> printQueue; 
    searchDependencies(searchFile, adjacencyList, printQueue);
    for(int i = printQueue.size() - 1; i >= 0; i--)
    {
        cout << printQueue.at(i) << endl; 
    }


}