struct RollingHash{
    int n;
    vector<unsigned long long> hash, power; // hash[k] -> [0, k) (0-indexed)

    RollingHash(const string &s) : n((int)s.size()){
        hash.assign(n + 1, 0);
        power.assign(n + 1, 0);
        hash[0] = 0;
        power[0] = 1;
        for(int i = 0; i < n; i++){
            power[i + 1] = CalcMod(Mul(power[i], Base));
            hash[i + 1] = CalcMod(Mul(hash[i], Base) + s[i]);
        }
    }

private : 
    unsigned int Base = 10007;
    const unsigned long long MOD = (1UL << 61) - 1;
    const unsigned long long POSITIVIZER = MOD * ((1UL << 3) - 1);
    const unsigned long long MASK30 = (1UL << 30) - 1;
    const unsigned long long MASK31 = (1UL << 31) - 1;
    const unsigned long long MASK61 = MOD;

    unsigned long long CalcMod(unsigned long long x){
        unsigned long long xu = x >> 61;
        unsigned long long xd = x & MASK61;
        unsigned long long res = xu + xd;
        if(res >= MOD) res -= MOD;
        return res;
    }

    // a * b
    unsigned long long Mul(unsigned long long a, unsigned long long b){
        unsigned long long au = a >> 31;
        unsigned long long ad = a & MASK31;
        unsigned long long bu = b >> 31;
        unsigned long long bd = b & MASK31;
        unsigned long long mid = au * bd + bu * ad;
        unsigned long long midu = mid >> 30;
        unsigned long long midd = mid & MASK30;
        return ((au * bu) << 1) + midu + (midd << 31) + ad * bd;
    }

    unsigned long long Mul(unsigned long long a, unsigned int b){
        unsigned long long au = a >> 31;
        unsigned int bd = b & MASK31;
        unsigned long long middleBit= au * bd;
        return (a & MASK31) * bd + ((middleBit & MASK30) << 31) + (middleBit >> 30);
    }

public : 
    //[l, r)
    unsigned long long get(int l, int r){
        return CalcMod(hash[r] + POSITIVIZER - Mul(hash[l], power[r - l]));
    }

    unsigned long long all(){ return get(0, n);}

    bool match(int l1, int r1, int l2, int r2){
        return get(l1, r1) == get(l2, r2);
    }
    // longest common suffix between [l1, r1) and [l2, r2)
    int LCP(int l1, int r1, int l2, int r2){
        int len = min(r1 - l1, r2 - l2);
        int ok = 0, ng = len + 1;
        while(abs(ok - ng) > 1){
            int mid = (ok + ng) / 2;
            if(match(l1, l1 + mid, l2, l2 + mid)) ok = mid;
            else ng = mid;
        }
        return ok;
    }
};
