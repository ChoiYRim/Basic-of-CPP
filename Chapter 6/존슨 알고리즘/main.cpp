#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge
{
    int src;
    int dst;
    int weight;
};

const int UNKNOWN = INT_MAX;

// check negative cycle exists
bool HasNegativeCycle(const vector<Edge>& edges,vector<int> distance)
{
    for(auto& e : edges)
    {
        if(distance[e.src] == UNKNOWN)
            continue;
        
        if(distance[e.src]+e.weight < distance[e.dst])
            return true;
    }
    
    return false;
}

vector<int> BellmanFord(vector<Edge> edges,int V)
{
    int s = V; // dummy node
    vector<int> distance(V+1,UNKNOWN);
    
    for(int i = 0; i < V; i++)
        edges.push_back(Edge{s,i,0}); // edge weight of [s,i] is 0.
    
    distance[s] = 0;
    for(int i = 0; i < V; i++)
    {
        for(auto& e : edges)
        {
            if(distance[e.src] == UNKNOWN)
                continue;
            
            if(distance[e.dst] > distance[e.src]+e.weight)
            {
                distance[e.dst] = distance[e.src]+e.weight;
            }
        }
    }
    
    if(HasNegativeCycle(edges,distance))
    {
        cout << "Negative cycle detected!" << endl;
        return {};
    }
    
    return distance;
}

int GetMinDistance(vector<int>& distance,vector<bool>& visited)
{
    int minDistance = UNKNOWN;
    int minIndex = -1;
    
    for(int i = 0; i < distance.size(); i++)
    {
        if(!visited[i] && distance[i] <= minDistance)
        {
            minDistance = distance[i];
            minIndex = i;
        }
    }
    
    return minIndex;
}

auto Dijkstra(vector<Edge> edges,int V,int start)
{
    vector<int> distance(V,UNKNOWN);
    vector<bool> visited(V,false);
    
    distance[start] = 0;
    for(int i = 0; i < V-1; i++)
    {
        int cur = GetMinDistance(distance,visited);
        visited[cur] = true;
        
        for(auto& e : edges)
        {
            if(e.src != cur)
                continue;
            if(visited[e.dst])
                continue;
            if(distance[cur] == UNKNOWN)
                continue;
            
            if(distance[e.dst] > distance[cur]+e.weight)
                distance[e.dst] = distance[cur]+e.weight;
        }
    }
    
    return distance;
}

void Johnson(vector<Edge> edges,int V)
{
    vector<int> h = BellmanFord(edges,V);
    
    if(h.empty())
        return;
    
    // reset edge weights
    for(auto& e : edges)
        e.weight += (h[e.src]-h[e.dst]);
    
    vector<vector<int>> shortest(V);
    for(int i = 0; i < V; i++)
        shortest[i] = Dijkstra(edges,V,i);
    
    // print shortest path
    for(int i = 0; i < V; i++)
    {
        cout << i << ":\n";
        for(int j = 0; j < V; j++)
        {
            if(shortest[i][j] != UNKNOWN)
            {
                shortest[i][j] += h[j]-h[i];
                cout << "\t" << j << ": " << shortest[i][j] << endl;
            }
        }
    }
}

int main(int argc,char* argv[])
{
    int V = 5;
    vector<Edge> edges;
    
    vector<vector<int>> edge_map{{0,1,-7},{1,2,-2},{2,0,10},{0,3,-5},{0,4,2},{3,4,4}};
    for(auto& e : edge_map)
        edges.emplace_back(Edge{e[0],e[1],e[2]});
    
    Johnson(edges,V);
    return 0;
}
