struct Graph{
    struct Edge{
        int to; long long cost;
        Edge(int to, long long cost) : to(to), cost(cost) {}
    };
    int num;
    const long long INF = std::numeric_limits<long long>::max();
    std::vector<std::vector<Edge>> G;
    std::vector<long long> dist;

    Graph(int n) : num(n){
        G.resize(n), dist.resize(n);
    }

    void add_edge(ll s, ll t, ll cost, bool directed){
        G[s].emplace_back(t, cost);
        if(!directed) G[t].emplace_back(s, cost);
    }

    long long dijkstra(int s, int g){
        std::fill(dist.begin(), dist.end(), INF);
        using P = pair<long long, int>;
        std::priority_queue<P, vector<P>, greater<P>> que;
        que.push({dist[s] = 0, s});
        while(!que.empty()){
            P p = que.top(); que.pop();
            int v = p.second;
            if(dist[v] < p.first) continue;
            for(auto e : G[v]){
                if(dist[e.to] > dist[v] + e.cost){
                  dist[e.to] = dist[v] + e.cost;
                  que.push({dist[e.to], e.to});
                }
            }
        }
        return dist[g];
    }
};
