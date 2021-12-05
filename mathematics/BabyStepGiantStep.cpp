struct BabyStepGiantStep{
private:
    long long g, p;
    long long m, ginvm;
    std::unordered_map<long long, int> table;

    long long modpow(long long a, long long p, long long mod){
        long long ret = 1; 
        while(p){
            if(p & 1) ret = ret * a % mod;
            a = a * a % mod;
            p >>= 1;
        }
        return ret;
    }

    void init(long long g){
        long long cur = 1;
        for(int i = 0; i < m; i++){
            table[cur] = i;
            cur = cur * g % p;
            if(cur == 1) break;
        }
        ginvm = modpow(modpow(g, p - 2, p), m, p);
        return;
    }

public:
    BabyStepGiantStep(long long _g, long long _p):g(_g), p(_p){
        g %= p;
        long long ok = p, ng = 0;
        while(ok - ng > 1){
            long long mid = (ok + ng) / 2;
            if(mid * mid >= p) ok = mid;
            else ng = mid;
        }
        m = ok;
        init(g);
    }

    // g^x = y mod p → return x
    long long solve(long long y){
        y %= p;
        long long cur = y;
        for(int i = 0; i < m; i++){
            if(table.find(cur) != table.end()){
                int j = table[cur];
                return m * i + j;
            }
            else cur = (cur * ginvm) % p;
        }
        return -1;
    }
};
