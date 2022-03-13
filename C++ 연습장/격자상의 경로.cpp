#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<int>> dp;

void print_dp()
{
    for(int i = 0; i < dp.size(); i++)
    {
        for(int j = 0; j < dp[i].size(); j++)
            printf("%-6d ", dp[i][j]);
        printf("\n");
    }
}

void init(int y,int x)
{
    dp = vector<vector<int>>(y,vector<int>(x,0));
    for(int i = 0; i < x; i++)
        dp[0][i] = 1;
    for(int i = 0; i < y; i++)
        dp[i][0] = 1;
    
    for(int i = 1; i < y; i++)
    {
        for(int j = 1; j < x; j++)
        {
            dp[i][j] = dp[i-1][j]+dp[i][j-1];
        }
    }
}

int main(int argc,char* argv[])
{
    init(10,10);
    print_dp();
    return 0;
}
