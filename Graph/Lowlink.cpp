// verified : https://onlinejudge.u-aizu.ac.jp/solutions/problem/GRL_3_A/review/6066708/sooh/C++17

struct Lowlink{
private:
    int n, cnt;
    int root;
    std::vector<std::vector<int>> G;
    std::vector<int> ord;
    std::vector<int> par;
    std::vector<bool> arp;
    std::vector<int> low;

    void dfs(int v, int p = -1){
        ord[v] = cnt++;
        par[v] = p;
        low[v] = ord[v];
        bool is_arp = false;
        int count = 0;
        for(int nv : G[v]){
            if(nv == p) continue;
            if(ord[nv] != -1){ // 後退辺
                low[v] = std::min(low[v], ord[nv]);
                continue;
            }
            dfs(nv, v);
            low[v] = std::min(low[v], low[nv]);
            is_arp |= ord[v] <= low[nv];
            count++;
        }
        arp[v] = is_arp;
        if(p == -1) arp[v] = count >= 2;
    }

public:
    Lowlink(int _n):n(_n), G(_n), ord(_n, -1), par(_n), arp(_n), low(_n){}

    void add_edge(int u, int v, bool directed = false){
        G[u].push_back(v);
        if(!directed) G[v].push_back(u);
    }
    void build(int _root = 0){
        root = _root;
        cnt = 0;
        dfs(root);
    }    
    bool is_bridge(int u, int v){return (par[v] == u ? ord[u] < low[v] : ord[v] < low[u]);}
    bool is_articulation_point(int v){return arp[v];}
};
