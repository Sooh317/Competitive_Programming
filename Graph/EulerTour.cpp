// unverified

struct EulerTour{
private:
    int cnt;
    void dfs(int v){
        for(int nv : G[v]){
            in[nv] = cnt;
            edge_tour[cnt++] = nv;
            dfs(nv);
        }
        out[v] = cnt;
        edge_tour[cnt++] = -v;
    }
public:
    int n;
    std::vector<std::vector<int>> G;
    std::vector<int> par;
    std::vector<int> in, out;
    std::vector<int> edge_tour;
    std::vector<int> vertex_tour;

    EulerTour(int _n):n(_n), G(_n), par(_n), in(_n), out(_n), cnt(1), edge_tour(2*_n), vertex_tour(2*_n - 1){}

    void add_edge(int u, int v){
        G[u].push_back(v);
        par[v] = u;
    }
    void build(){
        edge_tour[0] = 0;
        dfs(0);
        for(int i = 0; i < 2*n - 1; i++) vertex_tour[i] = (edge_tour[i] >= 0 ? edge_tour[i] : par[-edge_tour[i]]);
    }
};
