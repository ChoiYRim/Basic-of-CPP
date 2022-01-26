#include <stack>
#include <vector>
#include <iostream>

using namespace std;

// dfs
void FillStack(int node,vector<bool>& visited,vector<vector<int>>& adj,stack<int>& stack)
{
    visited[node] = true;
    for(auto& next : adj[node])
    {
        if(!visited[next])
        {
            FillStack(next,visited,adj,stack);
        }
    }
    
    stack.push(node);
}

vector<vector<int>> Transpose(int V,vector<vector<int>>& adj)
{
    vector<vector<int>> transpose(V);
    
    for(int i = 0; i < V; i++)
    {
        for(auto& next : adj[i])
        {
            transpose[next].push_back(i);
        }
    }
    
    return transpose;
}

// second dfs
void CollectConnectedComponents(int node,vector<bool>& visited,vector<vector<int>>& adj,vector<int>& component)
{
    visited[node] = true;
    component.push_back(node);
    
    for(auto& next : adj[node])
    {
        if(!visited[next])
        {
            CollectConnectedComponents(next,visited,adj,component);
        }
    }
}

vector<vector<int>> Kosaraju(int V,vector<vector<int>>& adj)
{
    vector<bool> visited(V,false);
    stack<int> stack;
    
    for(int i = 0; i < V; i++)
    {
        if(!visited[i])
        {
            FillStack(i,visited,adj,stack);
        }
    }
    
    vector<vector<int>> transpose = Transpose(V,adj);
    fill(visited.begin(),visited.end(),false);
    
    vector<vector<int>> connectedComponents;
    while(!stack.empty())
    {
        int node = stack.top();
        stack.pop();
        
        if(!visited[node])
        {
            vector<int> component;
            CollectConnectedComponents(node,visited,transpose,component);
            connectedComponents.push_back(component);
        }
    }
    
    return connectedComponents;
}

int main()
{
    int V = 10;
    vector<vector<int>> adj;
    
    // input
    
    vector<vector<int>> connectedComponents = Kosaraju(V,adj);
    
    // output
    
    return 0;
}
