struct Graph{
    const long long _INF = std::numeric_limits<long long>::max();
    struct Edge{
        int to; long long cost;
        Edge(int to, long long cost) : to(to), cost(cost) {}
    };
    int num;
    std::vector<std::vector<Edge>> G;
    std::vector<long long> dist;
    // constructor for initialization
    Graph(int n) : num(n){
        G.resize(n), dist.resize(n);
    }
    // assembling a graph whose edge is coming from s to t
    void add_edge(ll s, ll t, ll cost, bool directed){
        G[s].emplace_back(t, cost);
        if(!directed) G[t].emplace_back(s, cost);
    }
    // dijkstra algorithm
    ll dijkstra(int s, int g){
        std::fill(dist.begin(), dist.end(), _INF);
        using P = pair<ll, int>;
        std::priority_queue<P, vector<P>, greater<P>> que;
        que.push({dist[s] = 0, s});
        while(!que.empty()){
            P p = que.top(); que.pop();
            int v = p.second;
            if(dist[v] < p.first) continue;
            for(auto e : G[v]){

                if(chmin(dist[e.to], dist[v] + e.cost)) que.push({dist[e.to], e.to});
            }
        }
        return dist[g];
    }
};
