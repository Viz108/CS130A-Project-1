#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std; 

main()
{
    unordered_map<string, vector<string>> adjacencyList; 

    int n; 
    cin >> n; 

    for(int i = 0; i < n; i++)
    {
        string currLine;
        getline(cin, currLine);

        string currFile = currLine.substr(0, currLine.find(":")); 
        currLine.erase(0, currLine.find(":") + 1); 
        while(currLine.length() != 0)
        {
            if(currLine.at(0) == ' ')
            {
                currLine.erase(0, 1);
            }

            string newDepend; 
            if(currLine.find(" ")) //Search for next dependency
            {
                newDepend = currLine.substr(0, currLine.find(" "));
                currLine.erase(0, currLine.find(" ") + 1);
            }
            else
            {
                newDepend = currLine; //EOL, rest of string is the next file
            }

            
        }
    }
}