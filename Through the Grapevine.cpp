#include <iostream>
#include <string>
#include <vector>
#include <queue> 
#include <map>

using namespace std; 

struct personInfo
{
    int skepticism; 
    vector<string> neighbors; 
    vector<string> talkedTo; 
    bool visited = false;
    bool talked = false;
};

void explore( map<string, personInfo> &queue, string currSearch, int daysToSearch, string talkedTo)
{
    
    queue.at(currSearch).visited = true; 
    
    bool alreadyTalkedTo = false;
        for(int i = 0; i < queue.at(currSearch).talkedTo.size(); i++)
    {
        if(queue.at(currSearch).talkedTo.at(i) == talkedTo)
        {
            alreadyTalkedTo = true;
        }
    }
    if(!alreadyTalkedTo)
    {
        queue.at(currSearch).skepticism--;
        queue.at(currSearch).talkedTo.push_back(talkedTo);
    }
    if(daysToSearch > 0 && !queue.at(currSearch).talked && queue.at(currSearch).skepticism <= 0)
    {
        queue.at(currSearch).talked = true; 
        for(int i = 0; i < queue.at(currSearch).neighbors.size(); i++)
        {
            explore(queue, queue.at(currSearch).neighbors.at(i), --daysToSearch, currSearch); 
        }
    }
}

main()
{
    int n, m, d; 
    cin >> n; //Num people
    cin >> m; //Num connections
    cin >> d; //Num days

    map<string, personInfo> queue; 

    for(int i = 0; i < n; i++)
    {
        string name; 
        int skepticism; 
        cin >> name; 
        cin >> skepticism; 

        personInfo tempPerson; 
        tempPerson.skepticism = skepticism; 
        queue.insert(pair{name,tempPerson});        
    }

    for(int i = 0; i < m; i++)
    {
        string origin; 
        string connection; 
        cin >> origin; 
        cin >> connection; 
        queue.at(origin).neighbors.push_back(connection);
        queue.at(connection).neighbors.push_back(origin);
    }

    string rumorStart; 
    cin >> rumorStart; 
    
    explore(queue, rumorStart, d, "");

    int numVisited; 
    for(const auto &p : queue)
    {
        if(p.second.visited)
        {
            numVisited++; 
        }
    }

    numVisited--; //Remove 1 for rumor starter

    cout << numVisited << endl; 

    // for(const auto &p : queue)
    // {
    //     cout << p.first << ":" << endl; 
    //     for(int i = 0; i < p.second.neighbors.size(); i++)
    //     {
    //         cout << "   " << p.second.neighbors.at(i) << endl; 
    //     }
    //     cout << "Visited: " << p.second.visited << endl; 
    //     cout << "Talked: " << p.second.talked << endl; 
    //     cout << "Skepticsm: " << p.second.skepticism << endl; 
    // }
}