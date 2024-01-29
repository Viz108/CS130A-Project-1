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
    int dayVisited = 1; 
    vector<string> neighbors; 
    vector<string> talkedTo; 
    set<string> visitedBy; 
    bool visited = false;
    bool talked = false;
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
    adjacencyList.at(rumorStart).dayVisited = 1; 
    queue<string> BFSQueue; 
    BFSQueue.push(rumorStart); 
    while(BFSQueue.size() > 0)
    {
        cout << "Currently visiting " << BFSQueue.front() << " on day " << adjacencyList.at(BFSQueue.front()).dayVisited << endl; 
        if(adjacencyList.at(BFSQueue.front()).visited == false)
        {
            cout << "   First time visiting" << endl; 
            adjacencyList.at(BFSQueue.front()).visited = true; 
            peopleHeard++;
        }

        if(!(adjacencyList.at(BFSQueue.front()).talked) && (adjacencyList.at(BFSQueue.front()).visitedBy.size() >= adjacencyList.at(BFSQueue.front()).skepticism) && adjacencyList.at(BFSQueue.front()).dayVisited < d)
        {
            cout << "   Spreading rumor" << endl;
            for(int i = 0; i < adjacencyList.at(BFSQueue.front()).neighbors.size(); i++)
            {
                cout << "   Talking to " << adjacencyList.at(BFSQueue.front()).neighbors.at(i) << endl; 
                BFSQueue.push(adjacencyList.at(BFSQueue.front()).neighbors.at(i)); 
                adjacencyList.at(adjacencyList.at(BFSQueue.front()).neighbors.at(i)).dayVisited = adjacencyList.at(BFSQueue.front()).dayVisited + 1;    
                adjacencyList.at(adjacencyList.at(BFSQueue.front()).neighbors.at(i)).visitedBy.insert(BFSQueue.front()); 
            }
            adjacencyList.at(BFSQueue.front()).talked = true;
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

    for(const auto &p : adjacencyList)
    {
        cout << p.first << ":" << endl; 
        for(int i = 0; i < p.second.neighbors.size(); i++)
        {
            cout << "   " << p.second.neighbors.at(i) << endl; 
        }
        cout << "Visited: " << p.second.visited << endl; 
        cout << "Talked: " << p.second.talked << endl; 
        cout << "Skepticsm: " << p.second.skepticism << endl; 
        cout << "Day visited: " << p.second.dayVisited << endl; 
    }
}