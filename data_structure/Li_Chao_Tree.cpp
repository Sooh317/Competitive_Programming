template<typename T>
struct LiChaoTree{
private:
    const T INF = numeric_limits<T>::max();
    struct line{
        T m, n;
        line(T m, T n) : m(m), n(n){}
        T operator()(T x) const{return m*x + n;}
    };
    int N;
    vector<line> fs; // lines
    vector<T> xs; // coordinates

    int index(T x) const{return lower_bound(xs.begin(), xs.end(), x) - xs.begin();}

    void update(T m, T n, int l, int r){
        line g(m, n);
        for(l += N, r += N; l < r; l >>= 1, r >>= 1){
            if(l & 1) descend(g, l++);
            if(r & 1) descend(g, --r);
        }
    }

    void descend(line g, int i){
        int l = i, r = i + 1;
        while(l < N) l <<= 1, r <<= 1;
        while(l < r){
            int mid = (l + r) >> 1;
            T xl = xs[l - N], xr = xs[r - 1 - N], xmid = xs[mid - N];
            line &f = fs[i];
            if(f(xl) <= g(xl) && f(xr) <= g(xr)) return;
            if(f(xl) >= g(xl) && f(xr) >= g(xr)){ f = g; return;}
            if(f(xmid) > g(xmid)) swap(f, g);
            if(f(xl) > g(xl)) i = i << 1 | 0, r = mid;
            else i = i << 1 | 1, l = mid;
        }
    }

public:
    LiChaoTree(const vector<T> &xs_) : xs(xs_){
        // if x is already sorted when given in the input, you don't need this
        sort(xs.begin(), xs.end());
        // if no pair of coordinates intersect, you don't need this
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        N = xs.size();
        fs.assign(N << 1, line(T(0), INF));
    }
    // insert a line "mx + n"
    void insert_line(T m, T n){ update(m, n, 0, N);}
    // insert a line segment "mx + n for x ∈ [xl, xr)"
    void insert_segment(T m, T n, T xl, T xr){
        int l = index(xl), r = index(xr);
        update(m, n, l, r);
    }
    // return minimum value at x 
    T query(T x) const {
        int i = index(x);
        T res = INF;
        for(i += N; i; i >>= 1) res = min(res, fs[i](x));
        return res;
    }
};
