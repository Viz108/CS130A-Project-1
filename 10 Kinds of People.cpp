#include <iostream>
#include <string>

using namespace std; 

bool explore(int r, int c, int target_r, int target_c, int target_value)
{
    if(r == target_r && c == target_c )
    {
        
    }
}

main()
{
    int r, c; 
    cin >> r; 
    cin >> c; 

    int matrix[r][c]; 

    for(int i = 0; i < r; i++)
    {

        string newRow; 
        cin >> newRow; 
        for(int j = 0; j < c; j++)
        {
            matrix[i][j] = (int)newRow.at(j) - 48; 
        }
    }


    int n; 
    cin >> n;

    for(int i = 0; i < n; i++)
    {
        int r1, c1, r2, c2; 
        cin >> r1; 
        cin >> c1; 
        cin >> r2; 
        cin >> c2;

        int target = matrix[r1][c1]; 


    }
}