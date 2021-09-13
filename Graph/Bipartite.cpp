// bipartite_matching : verified in https://judge.yosupo.jp/submission/59973
// others : unverified
struct Bipartite_Graph{
private:
    int n;
    int lsize, rsize;
    int matching_num;
    std::vector<std::vector<int>> G;
    std::vector<int> match;

public:
    Bipartite_Graph(int a, int b):lsize(a), rsize(b), n(a + b), matching_num(-1){
        G.resize(n);
        match.resize(n, -1);
    }

    void add_edge(int u, int v){ 
        G[u].push_back(v);
        G[v].push_back(u);
    }

    // reference : https://snuke.hatenablog.com/entry/2019/05/07/013609
    int bipartite_matching(){
        int res = 0;
        std::vector<int> pre(lsize, -1);
        std::vector<int> root(lsize, -1);
        bool update = true;
        while(update){
            update = false;
            std::queue<int> que;
            for(int i = 0; i < lsize; i++){
                if(!~match[i]){
                    root[i] = i;
                    que.push(i);
                }
            }
            while(que.size()){
                int v = que.front(); que.pop();
                if(~match[root[v]]) continue;
                assert(v < lsize);
                for(int nv : G[v]){
                    if(!~match[nv]){
                        while(~nv){
                            match[nv] = v;
                            std::swap(match[v], nv);
                            v = pre[v];
                        }
                        update = true;
                        ++res;
                        break;
                    }
                    nv = match[nv];
                    if(~pre[nv]) continue;
                    pre[nv] = v, root[nv] = root[v];
                    que.push(nv);
                }
            }
            if(update){
                std::fill(pre.begin(), pre.end(), -1);
                std::fill(root.begin(), root.end(), -1);
            }
        }
        return matching_num = res;
    }

    int pair(int u){
        assert(~matching_num);
        return match[u];
    }

    // if there exists no edge_cover, return empty vector
    std::vector<std::pair<int, int>> minimum_edge_cover(){
        assert(~matching_num);
        std::vector<std::pair<int, int>> res;
        for(int i = 0; i < n; i++) if(G[i].size() == 0) return res;
        res.resize(n - matching_num);
        int idx = 0;
        for(int i = 0; i < n; i++){
            if(i < match[i]) res[idx++] = {i, match[i]};
            else if(match[i] == -1) res[idx++] = {i, G[i].back()};
        }
        assert(n - matching_num == idx);
        return res;
    }

    std::pair<std::vector<int>, std::vector<int>> minimum_vertex_cover(){
        assert(~matching_num);
        std::vector<bool> reachable(n);
        for(int i = 0; i < lsize; i++){
            if(match[i] != -1) continue;
            std::queue<int> que;
            que.push(i);
            while(que.size()){
                int v = que.front(); que.pop();
                reachable[v] = true;
                for(const int &nv : G[v]){
                    if(reachable[nv]) continue;
                    if(v >= lsize && match[v] == nv){
                        reachable[nv] = true;
                        que.push(nv);
                    }
                    if(v < lsize && match[v] != nv){
                        reachable[nv] = true;
                        que.push(nv);
                    }
                }
            }
        } 
        std::vector<int> left, right;
        for(int i = 0; i < n; i++){
            if(i < lsize && !reachable[i]) left.emplace_back(i);
            if(i >= lsize && reachable[i]) right.emplace_back(i);
        }  
        return std::make_pair(left, right);
    }   

    std::pair<std::vector<int>, std::vector<int>> stable_set(){
        assert(~matching_num);
        std::vector<int> left, right;
        auto p = minimum_vertex_cover();
        std::vector<bool> complement(n);
        for(const int &v : p.first) complement[v] = true;
        for(const int &v : p.second) complement[v] = true;
        for(int i = 0; i < n; i++){
            if(complement[i]) continue;
            if(i >= lsize) right.emplace_back(i);
            else left.emplace_back(i);
        }
        return std::make_pair(left, right);
    }
};
