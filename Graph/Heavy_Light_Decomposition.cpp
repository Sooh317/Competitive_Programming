// verified : https://judge.yosupo.jp/submission/56777
template <class T> 
struct HLD{
    // hld : HLDの列, in : hldにおける位置, nxt : 分解後連結成分の親
    int n, cnt; 
    vector<vector<int>> G;
    vector<int> in, par, hld, nxt, sz;

    // for queries on subtrees
    // out can be calculated like out = in + sz 
    // vector<int> rev; 

private:
    int dfs(int v, int p = -1){
        par[v] = p;
        sz[v] = 1;
        for(int& nv : G[v]){
            if(nv == p) continue;
            sz[v] += dfs(nv, v);
            if(sz[nv] > sz[G[v][0]]) swap(nv, G[v][0]);
        }
        return sz[v];
    }

    void Heavy_Light_Decomposition(int v, int p = -1){
        in[v] = cnt++;
        //rev[in[v]] = v;
        hld.pb(v);
        for(int nv : G[v]){
            if(nv == p) continue;
            nxt[nv] = (nv == G[v][0] ? nxt[v] : nv);
            Heavy_Light_Decomposition(nv, v);
        }
    }


public:
    HLD(int _n) : n(_n){
        G.resize(n);
        par.resize(n);
        nxt.resize(n);
        sz.resize(n);
        in.resize(n);
        cnt = 0;
        // rev.resize(n);
    }

    void add_edge(int u, int v){
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    void add_directed_edge(int u, int v){ G[u].emplace_back(v);}

    void build(int root = 0){
        dfs(root);
        Heavy_Light_Decomposition(root);
    }

    int lca(int u, int v){
        for(;; v = par[nxt[v]]){
            if(in[u] > in[v]) swap(u, v);
            if(nxt[u] == nxt[v]) return u;
        }
    }

    // qが区間に対する操作の関数 (bit.sumなど) (開区間で呼んでくれる)
    // fは異なる区間に対してどう繋ぎ合わせるかの関数 (和? 積?)
    // e : unit
    // edge : 辺にコストがある
    // 辺にコストがあるなら、葉側の頂点に移動させる
    template<typename Q, typename F>
    T query (int u, int v, const T& e, const Q& q, const F& f, bool edge = false){
        T l = e, r = e; // l, rは累積値
        for(;; v = par[nxt[v]]){
            if(in[u] > in[v]) swap(u, v), swap(l, r);
            if(nxt[u] == nxt[v]) break;
            l = f(q(in[nxt[v]], in[v] + 1), l);
        }
        return f(f(q(in[u] + edge, in[v] + 1), l), r);
    }
};
