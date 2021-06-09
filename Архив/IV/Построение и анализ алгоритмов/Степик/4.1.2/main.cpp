#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <map>
#include <limits>
using namespace std;

struct Adjacency_list {
    char Vertex_title;
    int w;
    int flow;
    int dist;
};
struct Vertex {
    char title;
    int dist;
};
struct DistanceCmp {
    bool operator()(Vertex const& p1, Vertex const& p2) {
        return p1.dist > p2.dist;
    }
};

class MF{
private:
    map<char, char> pr;
    map<char, map<char, Adjacency_list>> grph;
    char S;
    char T;
public:
    MF(char S, char T) {
        this->S = S;
        this->T = T;
    }
    void createEdge(char from, char to, int w) {
        int lenEdge = abs(from - to);
        grph[from][to] = { to, w, 0, lenEdge };
        if (grph.find(to) == grph.end() || grph[to].find(from) == grph[to].end()) {
            grph[to][from] = { from, 0, 0, lenEdge };
        }
    }
    bool path() {
        priority_queue<Vertex, vector<Vertex>, DistanceCmp> PriorityQueue;
        PriorityQueue.push({ S, 0 });
        map<char, bool> visited;
        while (!PriorityQueue.empty()) {
            char u = PriorityQueue.top().title;
            PriorityQueue.pop();
            visited[u] = true;
            for (auto x = grph[u].begin(); x != grph[u].end(); ++x) {
                char v = x->second.Vertex_title;
                int w = x->second.w;
                int flow = x->second.flow;
                int dist = x->second.dist;
                if (!visited[v] && w - flow > 0) {
                    PriorityQueue.push({ v, dist});
                    pr[v] = u;
                    if (v == T)
                        return true;
                }
            }
        }
        return false;
    }

    void findMax() {
        int maxF = 0;
        while (path()){
            int MRC = std::numeric_limits<int>::max();
            char v = T;
            while (v != S) {
                char u = pr[v];
                int RC = grph[u][v].w - grph[u][v].flow;
                MRC = std::min(RC, MRC);
                v = u;
            }
            v = T;
            while (v != S) {
                char u = pr[v];
                grph[u][v].flow += MRC;
                grph[v][u].flow -= MRC;
                v = u;
            }
            maxF += MRC;
        }
        cout << maxF << endl;
        for (auto it1 = grph.begin(); it1 != grph.end(); ++it1) {
            for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2) {
                if (it2->second.w > 0)
                {
                    if(it2->second.flow > 0)
                        cout << it1->first << " " << it2->first << " " << it2->second.flow << endl;
                    else
                        cout << it1->first << " " << it2->first << " " << "0" << endl;
                }
            }
        }
    }
};

int main(){
    int N, w;
    char S, T;
    cin >> N >> S >> T;
    MF f_farc(S, T);
    char from, to;
    for (int i = 0; i < N; i++){
        cin >> from >> to >> w;
        f_farc.createEdge(from, to, w);
    }
    f_farc.findMax();
    return 0;
}