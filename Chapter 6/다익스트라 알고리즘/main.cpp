#include <set>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>

struct Edge
{
    int src;
    int dst;
    int weight;
    
    inline bool operator<(const Edge& e) const
    {
        return weight < e.weight;
    }
    
    inline bool operator>(const Edge& e) const
    {
        return weight > e.weight;
    }
};

class Graph
{
public:
    Graph() = default;
    
    Graph(int v) : V(v) { }
    
    void set_vertices(int v) { V = v; }
    
    auto range(int v) { return (v >= 0 && v < V); }
    
    void add_edge(Edge&& e)
    {
        if(range(e.src) && range(e.dst))
            edge_list.emplace_back(e);
    }
    
    auto vertices() const { return V; }
    
    auto& edges() const { return edge_list; }
    
    auto edges(int node)
    {
        std::vector<Edge> edges_from_node;
        for(auto& e : edge_list)
        {
            if(e.src == node)
                edges_from_node.emplace_back(e);
        }
        
        return edges_from_node;
    }
    
private:
    int V; // 정점의 개수
    std::vector<Edge> edge_list;
};

int V,E,K;
Graph g;

void input()
{
    std::cin >> V >> E;
    std::cin >> K;
    g.set_vertices(V);
    for(int i = 0; i < E; i++)
    {
        int u,v,w; std::cin >> u >> v >> w;
        g.add_edge(Edge{u-1,v-1,w});
    }
    K--;
}

struct Label
{
    int idx;
    int dist;
    
    inline bool operator>(const Label& l) const
    {
        return dist > l.dist;
    }
    inline bool operator<(const Label& l) const
    {
        return dist < l.dist;
    }
};

auto dijkstra(int start)
{
    std::priority_queue<Label,std::vector<Label>,std::greater<Label>> pq;
    std::vector<int> dist(V,std::numeric_limits<int>::max());
    std::vector<int> parent(g.vertices()); // 경로 구성용
    std::set<int> visited; // 방문 확인용
    
    dist[start] = 0; // 시작 정점까지의 거리는 0이지
    parent[start] = 0;
    pq.push(Label{start,0});
    while(!pq.empty())
    {
        auto current = pq.top();
        pq.pop();
        
        if(visited.find(current.idx) == visited.end())
        {
            for(auto& e : g.edges(current.idx))
            {
                int near = e.dst;
                int dist_to_near = current.dist+e.weight;
                
                if(dist_to_near < dist[near])
                {
                    dist[near] = dist_to_near;
                    parent[near] = current.idx;
                    pq.push(Label{near,dist_to_near});
                }
            }
            
            visited.insert(current.idx);
        }
    }
    
    std::vector<int> shortest_path;
    for(int i = 0; i < V; i++)
    {
        if(i == start)
            continue;
        
        int dst = i;
        //std::cout << "[" << dst+1 << "번 정점까지의 경로]" << std::endl;
        while(dst != start)
        {
            shortest_path.push_back(dst);
            dst = parent[dst];
        }
    }
    
    shortest_path.push_back(start);
    std::reverse(shortest_path.begin(),shortest_path.end());
    
    // 여기서 최단 경로 출력하면 됨
    
    return dist;
}

int main()
{
    input();
    
    auto dist = dijkstra(K);
    for(auto& d : dist)
    {
        if(d == std::numeric_limits<int>::max())
            std::cout << "INF" << std::endl;
        else
            std::cout << d << std::endl;
    }
    return 0;
}
