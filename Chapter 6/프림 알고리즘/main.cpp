#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <limits>

using namespace std;

template <typename T>
struct Edge
{
    unsigned src;
    unsigned dst;
    T weight;
};

template <typename T>
class Graph
{
public:
    Graph(unsigned N) : V(N) { }

    auto vertices() const { return V; }
    
    auto& edges() const { return edge_list; }
    
    auto edges(unsigned v) const
    {
        vector<Edge<T>> edges_from_v;
        
        for(auto& e : edge_list)
        {
            if(e.src == v)
                edges_from_v.emplace_back(e);
        }
        
        return edges_from_v;
    }
    
    void add_edge(Edge<T>&& e)
    {
        if(e.src >= 1 && e.src <= V && e.dst >= 1 && e.dst <= V)
            edge_list.emplace_back(e);
    }
    
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os,const Graph<U>& G);
    
private:
    unsigned V;
    vector<Edge<T>> edge_list;
};

template <typename U>
std::ostream& operator<<(std::ostream& os,const Graph<U>& G)
{
    for(unsigned i = 1; i < G.vertices(); i++)
    {
        os << i << ":\t";
        auto edges = G.edges(i);
        for(auto& e : edges)
            os << "{" << e.dst << ": " << e.weight << "}, ";
        os << endl;
    }
    
    return os;
}

template <typename T>
auto create_reference_graph()
{
    Graph<T> G(9);
    map<unsigned,vector<pair<unsigned,T>>> inputs;
    
    inputs[1] = {{2,2},{5,3}};
    inputs[2] = {{1,2},{5,5},{4,1}};
    inputs[3] = {{4,2},{7,3}};
    inputs[4] = {{2,1},{3,2},{5,2},{6,4},{8,5}};
    inputs[5] = {{1,3},{2,5},{4,2},{8,3}};
    inputs[6] = {{4,4},{7,4},{8,1}};
    inputs[7] = {{3,3},{6,4}};
    inputs[8] = {{4,5},{5,3},{6,1}};
    
    for(auto& i : inputs)
        for(auto& j : i.second)
            G.add_edge(Edge<T>{i.first,j.first,j.second});
    
    return G;
}

template <typename T>
struct Label
{
    unsigned ID;
    T distance;
    
    inline bool operator>(const Label<T>& l) const
    {
        return distance > l.distance;
    }
};

template <typename T>
auto prim_MST(const Graph<T>& G,unsigned src)
{
    priority_queue<Label<T>,vector<Label<T>>,greater<Label<T>>> heap; // min heap
    vector<T> distance(G.vertices(),numeric_limits<T>::max()); // 모든 정점에서 거리 값을 최대로 설정
    set<unsigned> visited; // 방문한 정점
    vector<unsigned> MST;
    
    heap.emplace(Label<T>{src,0});
    while(!heap.empty())
    {
        auto current_vertex = heap.top(); // 거리 값이 가까운 순서부터 뽑기
        heap.pop();
        
        // not visited
        if(visited.find(current_vertex.ID) == visited.end())
        {
            MST.push_back(current_vertex.ID);
            
            for(auto& e : G.edges(current_vertex.ID))
            {
                auto neighbor = e.dst;
                auto new_distance = e.weight;
                
                // 인접한 정점의 거리 값이 새로운 경로에 의한 거리 값보다 크면
                // 힙에 추가하고 거리 값을 업데이트
                if(new_distance < distance[neighbor])
                {
                    heap.emplace(Label<T>{neighbor,new_distance});
                    distance[neighbor] = new_distance;
                }
            }
            
            visited.insert(current_vertex.ID);
        }
    }
    
    return MST;
}

int main()
{
    using T = unsigned;
    
    auto G = create_reference_graph<T>();
    cout << "[입력 그래프]" << endl;
    cout << G << endl;
    
    auto MST = prim_MST<T>(G,1);
    cout << "[최소 신장 트리]" << endl;
    for(auto v : MST)
        cout << v << endl;
    cout << endl;
    
    return 0;
}
