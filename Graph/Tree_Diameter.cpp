// verified: https://atcoder.jp/contests/abc221/submissions/28071945

struct Tree_Diameter{
private:
    int n;
    std::vector<int> dist;

    void dfs(int v, int p = -1){
        for(int nv : G[v]){
            if(nv == p) continue;
            dist[nv] = dist[v] + 1;
            dfs(nv, v);
        }
    }
    void bfs(int v){
        diameter.reserve(dist[v] + 1);
        diameter.push_back(v);
        while(dist[v] != 0){
            for(int nv : G[v]){
                if(dist[nv] == dist[v] - 1){
                    diameter.push_back(nv);
                    v = nv;
                    break;
                }
            }
        }
    }

public:
    std::vector<std::vector<int>> G;
    std::vector<int> diameter;

    Tree_Diameter(int _n):n(_n), G(_n), dist(_n){}

    void add_edge(int a, int b){
        G[a].push_back(b);
        G[b].push_back(a);
    }

    void build(){
        dfs(0);
        auto it = std::max_element(dist.begin(), dist.end());
        int idx = it - dist.begin();
        dist[idx] = 0;
        dfs(idx);
        it = std::max_element(dist.begin(), dist.end());
        idx = it - dist.begin();
        bfs(idx);
    }

    std::pair<int, int> center(){
        assert(diameter.size() > 0);
        return std::pair<int, int>(diameter[(diameter.size() - 1) / 2], diameter[(diameter.size()) / 2]);
    }
    
    int size(){return diameter.size();}
};
