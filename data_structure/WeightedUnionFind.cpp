// reference: https://qiita.com/drken/items/cce6fc5c579051e64fab#%E3%81%AF%E3%81%98%E3%82%81%E3%81%AB
// verified: https://atcoder.jp/contests/abc087/submissions/28093052

// the most general usage
int f(int a, int b){return a + b;}
int g(int a, int b){return a - b;}
int e(){return 0;}

// g = f^(-1)
template<typename T, T (*f)(T, T), T (*g)(T, T), T (*e)()>
struct WeightedUnionFind{
private:
    int n;
    std::vector<int> par, rank;
    std::vector<int> dw; // 親との差分
public:
    WeightedUnionFind(int _n):n(_n), rank(n, 0), dw(n, e()){
        par.resize(n);
        std::iota(par.begin(), par.end(), 0);
    }

    // y's parent is x and y - x = w
    int merge(int y, int x, T w){
        // weight += dw[x]; // root(x) <--> y
        // weight -= dw[y]; // root(x) <--> root(y)
        w = g(f(w, weight(x)), weight(y));
        x = leader(x), y = leader(y);
        if(x == y){
            if(w == 0) return x;
            else return -1;
        }
        if(rank[x] < rank[y]) std::swap(x, y), w = g(e(), w);
        else if(rank[x] == rank[y]) rank[x]++;
        par[y] = x;
        dw[y] = w;
        return x;
    }   

    int leader(int x){
        if(par[x] == x) return x;
        int p = leader(par[x]);
        dw[x] = f(dw[x], dw[par[x]]);
        return par[x] = p;
    }

    bool same(int x, int y){return leader(x) == leader(y);}

    T weight(int x){
        leader(x);
        return dw[x];
    }

    std::pair<T, bool> diff(int x, int y){return make_pair(weight(x) - weight(y), same(x, y));}

};
