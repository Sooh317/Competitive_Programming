class LCA{
    using Graph = vector<vector<int>>;

private:
    vector<vector<int>> parent;
    //vector<int> dep; // depth from the root
    void init(const Graph &G, int root = 0){
        int N = G.size(), K = 1;
        while((1<<K) < N) K++;
        parent.resize(K, vector<int>(N, -1));
        dep.assign(N, -1);
        dfs(G, root, -1);
        for(int k = 0; k < K - 1; k++){
            for(int v = 0; v < N; v++){
                if(parent[k][v] < 0) parent[k + 1][v] = -1;
                else parent[k + 1][v] = parent[k][parent[k][v]];
            }
        }
    }
    void dfs(const Graph &G, int v, int p, int d = 0){
        parent[0][v] = p;
        dep[v] = d;
        for(int nv : G[v]){
            if(nv == p) continue;
            dfs(G, nv, v, d + 1);
        }
    }  
 
public:
    vector<int> dep; // depth from the root
    
    LCA(const Graph &G, int root = 0){ init(G, root);}

    // Lowest Common Ancestor of u and v
    int query(int u, int v){
        if(dep[u] > dep[v]) swap(u, v);
        int K = parent.size();
        for(int k = 0; k < K; k++){
            if((dep[v] - dep[u]) >> k & 1) v = parent[k][v];
        }
        if(u == v) return u;
        for(int k = K - 1; k >= 0; k--){
            if(parent[k][u] != parent[k][v]){ 
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }
};
