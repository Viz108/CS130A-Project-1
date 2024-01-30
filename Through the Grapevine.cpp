#include <iostream>
#include <string>
#include <vector>
#include <queue> 
#include <map>
#include <set>

using namespace std; 

struct personInfo
{
    string name; 
    int skepticism; 
    vector<string> neighbors; 
    vector<string> talkedTo; 
    set<string> visitedBy; 
    bool visited = false;
    bool talked = false;
    bool dateLock = false; 
};

main()
{
    int n, m, d; 
    cin >> n; //Num people
    cin >> m; //Num connections
    cin >> d; //Num days

    map<string, personInfo> adjacencyList; 

    for(int i = 0; i < n; i++)
    {
        string name; 
        int skepticism; 
        cin >> name; 
        cin >> skepticism; 

        personInfo tempPerson; 
        tempPerson.name = name; 
        tempPerson.skepticism = skepticism; 
        adjacencyList.insert(pair{name,tempPerson});        
    }

    for(int i = 0; i < m; i++)
    {
        string origin; 
        string connection; 
        cin >> origin; 
        cin >> connection; 
        adjacencyList.at(origin).neighbors.push_back(connection);
        adjacencyList.at(connection).neighbors.push_back(origin);
    }

    string rumorStart; 
    cin >> rumorStart; 

    int peopleHeard = 0; 
    queue<pair<string,int>> BFSQueue; 
    BFSQueue.push(pair{rumorStart, 1}); 
    while(BFSQueue.size() > 0)
    {
        //cout << "Currently visiting " << BFSQueue.front() << " on day " << adjacencyList.at(BFSQueue.front()).dayVisited << endl; 
        if(adjacencyList.at(BFSQueue.front().first).visited == false)
        {
            //cout << "   First time visiting" << endl; 
            adjacencyList.at(BFSQueue.front().first).visited = true; 
            peopleHeard++;
        }

        if(!(adjacencyList.at(BFSQueue.front().first).talked) && (adjacencyList.at(BFSQueue.front().first).visitedBy.size() >= adjacencyList.at(BFSQueue.front().first).skepticism) && BFSQueue.front().second <= d)
        {
            //cout << "   Spreading rumor" << endl;
            for(int i = 0; i < adjacencyList.at(BFSQueue.front().first).neighbors.size(); i++)
            {
                //cout << "   Talking to " << adjacencyList.at(BFSQueue.front()).neighbors.at(i) << endl; 
                BFSQueue.push(pair{adjacencyList.at(BFSQueue.front().first).neighbors.at(i), BFSQueue.front().second + 1}); 
                //adjacencyList.at(adjacencyList.at(BFSQueue.front().first).neighbors.at(i)).dayVisited = adjacencyList.at(BFSQueue.front().first).dayVisited + 1;  

                adjacencyList.at(adjacencyList.at(BFSQueue.front().first).neighbors.at(i)).visitedBy.insert(BFSQueue.front().first); 
            }
            adjacencyList.at(BFSQueue.front().first).talked = true;
        }
        
        BFSQueue.pop();
    }

    peopleHeard--; 
    cout << peopleHeard << endl; 
    
    //explore(adjacencyList, rumorStart, d, "");

    // int numVisited; 
    // for(const auto &p : adjacencyList)
    // {
    //     if(p.second.visited)
    //     {
    //         numVisited++; 
    //     }
    // }

    // numVisited--; //Remove 1 for rumor starter

    // cout << numVisited << endl; 

    // for(const auto &p : adjacencyList)
    // {
    //     cout << p.first << ":" << endl; 
    //     for(int i = 0; i < p.second.neighbors.size(); i++)
    //     {
    //         cout << "   " << p.second.neighbors.at(i) << endl; 
    //     }
    //     cout << "Visited: " << p.second.visited << endl; 
    //     cout << "Talked: " << p.second.talked << endl; 
    //     cout << "Skepticsm: " << p.second.skepticism << endl; 
    //     cout << "Day visited: " << p.second.dayVisited << endl; 
    // }
}