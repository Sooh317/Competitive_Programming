struct PartialPersistentUnionfind{
    int n;
    int now;
    vector<int> par;
    vector<int> time;
    vector<vector<pair<int,int>>> sz;

    PartialPersistentUnionfind(int n)
        :n(n),
         now(0),
         par(n,-1),
         time(n,INF),
         sz(n,vector<pair<int,int>>(1,{0,1})) {}

    int find(int x,int t) {
        if (t < time[x]) return x;
        return find(par[x],t);
    }

    int unite(int x,int y) {
        ++now;
        x = find(x,now);
        y = find(y,now);
        if (x == y) return now;
        if (par[x] > par[y]) swap(x,y);
        par[x] += par[y];
        par[y] = x;
        time[y] = now;
        sz[x].emplace_back(now,-par[x]);
        return now;
    }

    int size(int x,int t) {
        int p = find(x,t);
        int left = 0,right = (int)sz[p].size();
        while (right - left > 1) {
            int mid = (left + right) / 2;
            if (sz[p][mid].first <= t) left = mid;
            else right = mid;
        }
        return sz[p][left].second;
    }

    bool same(int x,int y,int t) {
        return find(x,t) == find(y,t);
    }
};
