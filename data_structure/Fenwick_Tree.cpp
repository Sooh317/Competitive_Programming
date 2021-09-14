template<class T> struct BIT{
private:
    int _n, cnt;
    vector<T> data;
public:
    BIT(int n) : _n(n + 1), data(n + 1) {
        cnt = 1;
        while(cnt < n) cnt *= 2;
    };
    void add(int p, T x = 1){
        assert(0 <= p && p < _n);
        p++;
        for(;p < _n; p += p & -p) data[p] += x;
    }
    //[l, r)
    T sum(int l, int r){
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }
    //[0, r)
    T sum(int r){
        T sum = 0;
        for(; r > 0; r -= r & -r) sum += data[r];
        return sum;
    }
    //V0 + V1 + ... + Vpos >= val 
    int lower_bound(T val){
        if(val <= 0) return 0;
        int pos = 0;
        for(int k = cnt; k > 0; k >>= 1){
            int npos = pos + k;
            if(npos < _n && data[npos] < val){
                val -= data[npos];
                pos = npos;
            }
        }
        return pos;
    }
};
