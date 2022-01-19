#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <map>
#include <set>

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
auto create_bipartite_reference_graph()
{
    Graph<T> G(10);
    map<unsigned,vector<pair<unsigned,T>>> inputs;
    
    inputs[1] = {{2,0}};
    inputs[2] = {{1,0},{3,0},{8,0}};
    inputs[3] = {{2,0},{4,0}};
    inputs[4] = {{3,0},{6,0}};
    inputs[5] = {{7,0},{9,0}};
    inputs[6] = {{4,0}};
    inputs[7] = {{5,0}};
    inputs[8] = {{2,0},{9,0}};
    inputs[9] = {{5,0},{8,0}};
    
    for(auto& i : inputs)
        for(auto& j : i.second)
            G.add_edge(Edge<T>{i.first,j.first,j.second});
    
    return G;
}

template <typename T>
auto bipartite_check(const Graph<T>& G)
{
    enum class colors { NONE,BLACK,RED };
    
    stack<unsigned> stack;
    set<unsigned> visited;
    
    stack.push(1);
    colors current_color { colors::BLACK };
    vector<colors> vertex_colors(G.vertices(),colors::NONE);
    
    while(!stack.empty())
    {
        auto current_vertex = stack.top();
        stack.pop();
        
        if(visited.find(current_vertex) == visited.end())
        {
            visited.insert(current_vertex);
            vertex_colors[current_vertex] = current_color;
            
            if(current_color == colors::RED)
            {
                cout << current_vertex << "번 정점: 빨간색" << endl;
                current_color = colors::BLACK;
            }
            else
            {
                cout << current_vertex << "번 정점: 검은색" << endl;
                current_color = colors::RED;
            }
            
            for(auto e : G.edges(current_vertex))
                if(visited.find(e.dst) == visited.end())
                    stack.push(e.dst);
        }
        else if(vertex_colors[current_vertex] != colors::NONE && vertex_colors[current_vertex] != current_color)
        {
            // 현재 정점은 이미 색칠된(방문한) 상태이고 현재 칠할 색상과 같은 색상이 이미 칠해져있다면 이분 그래프가 아니다.
            return false;
        }
    }
    
    return true;
}

int main()
{
    using T = unsigned;
    
    auto BG = create_bipartite_reference_graph<T>();
    cout << "[입력 그래프]" << endl;
    cout << BG << endl;
    
    if(bipartite_check<T>(BG))
        cout << "이분 그래프가 맞습니다." << endl;
    else
        cout << "이분 그래프가 아닙니다." << endl;
    
    return 0;
}
