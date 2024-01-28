#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <queue>

using namespace std; 

void searchDependencies(string currentFile, map<string, vector<string>> &list, set<string> &visitedFiles, queue<string> &printQueue, set<string> &addedToPrint)
{
    // cout << "currently exploring " << currentFile << endl; 
    // cout << "visited files are: " << endl; 
    // for(auto& str : visitedFiles)
    // {
    //     cout << str << endl; 
    // }
    // cout << endl; 

    // cout << "print queue is currently: " << endl; 
    // for(auto& str : addedToPrint)
    // {
    //     cout << str << endl; 
    // }
    // cout << endl; 

    visitedFiles.insert(currentFile); 
    for(int i = 0; i < list[currentFile].size(); i++)
    {
        if(addedToPrint.find(list[currentFile][i]) == addedToPrint.end())
        {
            // cout << "adding " << list[currentFile][i] << " to print queue" << endl; 
            // cout << endl; 
            printQueue.push(list[currentFile][i]); 
            addedToPrint.insert(list[currentFile][i]);
        }
    }
    for(int i = 0; i < list[currentFile].size(); i++)
    {
        if(visitedFiles.find(list[currentFile][i]) == visitedFiles.end())
        {
            searchDependencies(list[currentFile][i], list, visitedFiles, printQueue, addedToPrint); 
        }
    }
}

main()
{
    map<string, vector<string>> adjacencyList; 

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
        adjacencyList.insert(pair{currFile, vector<string>()}); 

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
                adjacencyList[newDepend].push_back(currFile); 
            }
            else
            {
                adjacencyList.insert(pair{newDepend, vector<string>()}); 
                adjacencyList[newDepend].push_back(currFile); 
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
    set<string> visitedFilesList; 
    queue<string> printQueueList; 
    set<string> queuedPrintFiles; 
    printQueueList.push(searchFile); 
    searchDependencies(searchFile, adjacencyList, visitedFilesList, printQueueList, queuedPrintFiles); 
    while(!printQueueList.empty())
    {
        cout << printQueueList.front() << endl; 
        printQueueList.pop(); 
    }
}