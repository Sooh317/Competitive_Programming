// verified: https://onlinejudge.u-aizu.ac.jp/status/users/sooh/submissions/1/DSL_2_A/judge/6151320/C++17

template<typename T, T (*op)(T, T), T (*e)()>
struct RMQ{
    int n;
    int bsize;
    std::vector<T> A;
    std::vector<T> bucket;

    Sqrt_Decomposition(const std::vector<T>& a):n(a.size()), A(a.begin(), a.end()){
        bsize = (int)std::sqrt(n);
        bucket.resize((int)A.size() / bsize);
        int idx = 0;
        for(int i = 0; i < (int)bucket.size(); i++){
            T val = e();
            for(int j = 0; j < bsize; j++) val = op(val, A[idx++]);
            bucket[i] = val;
        }
    }

    T prod(int l, int r){
        assert(0 <= l && l <= r && r <= n);
        int pos = l;
        T val = e();
        while(pos < r){
            if(pos % bsize || r - pos < bsize) val = op(val, A[pos++]);
            else{
                val = op(val, bucket[pos / bsize]);
                pos += bsize;
            }
        }
        return val;
    }

    T all_prod(){return prod(0, n);}

    void set(int x, T v){
        T val = e();
        A[x] = v;
        int bp = x / bsize;
        for(int i = bp * bsize; i < bp * bsize + bsize; i++) val = op(val, A[i]);
        bucket[bp] = val;
    }

};
