#include <vector>
#include <iostream>
#include <climits>

const int UNKNOWN = INT_MAX;

struct Edge
{
    int src;
    int dst;
    int weight;
};

auto BellmanFord(const std::vector<Edge>& edges,int V,int start)
{
    std::vector<int> distance(V,UNKNOWN);
    
    distance[start] = 0;
    
    // (V-1)번 반복
    for(int i = 0; i < V-1; i++)
    {
        // 전체 엣지에 대해 반복
        for(auto& e : edges)
        {
            // 엣지의 시작 정점의 거리 값이 UNKNOWN이면 pass
            if(distance[e.src] == UNKNOWN)
                continue;
            
            if(distance[e.dst] > distance[e.src]+e.weight)
            {
                distance[e.dst] = distance[e.src]+e.weight;
            }
        }
    }
    
    for(auto& e : edges)
    {
        if(distance[e.src] == UNKNOWN)
            continue;
        
        if(distance[e.dst] > distance[e.src]+e.weight)
        {
            std::cout << "음수 가중치 발견" << std::endl;
            distance.clear();
            break;
        }
    }
    
    return distance;
}

int main()
{
    int V = 5,start = 0;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> edge_map{{0,1,3},{1,2,5},{1,3,10},{3,2,-7},{2,4,2}};
    
    for(auto& e : edge_map)
        edges.emplace_back(Edge{e[0],e[1],e[2]});
    
    std::vector<int> distance = BellmanFord(edges,V,start);
    
    std::cout << "[" << start << "번 정점으로부터 최소 거리]" << std::endl;
    for(int i = 0; i < distance.size(); i++)
    {
        if(distance[i] != UNKNOWN)
            std::cout << i << "번 정점: " << distance[i] << std::endl;
        else
            std::cout << i << "번 정점: 방문하지 않음" << std::endl;
    }
    
    return 0;
}
