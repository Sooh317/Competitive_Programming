// reference : https://qiita.com/keymoon/items/11fac5627672a6d6a9f6#rollinghash%E3%81%AB%E7%B5%84%E3%81%BF%E8%BE%BC%E3%82%80%E9%9A%9B%E3%81%AB%E5%B7%A5%E5%A4%AB%E3%81%99%E3%82%8B%E3%81%A8%E8%89%AF%E3%81%84%E3%81%93%E3%81%A8
// verified : https://atcoder.jp/contests/arc130/submissions/27918813
struct RollingHash{
struct RandomNumberGenerator{
    std::mt19937_64 mt;
    RandomNumberGenerator() : mt(std::chrono::steady_clock::now().time_since_epoch().count()) {}
    long long operator()(long long a, long long b) { // [a, b)
        std::uniform_int_distribution< long long > dist(a, b - 1);
        return dist(mt);
    }
    long long operator()(long long b){return (*this)(0, b);} // [0, b)
};
    using u64 = unsigned long long;
    std::vector<u64> hash; // hash[k] = s[0]*b^(k-1) + s[1]*b^(k-2) + ... + s[k-1]
    RollingHash(const std::string &s) : n((int)s.size()){
        RandomNumberGenerator rng;
        Base = rng(100000,50000000);
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
    int n;
    std::vector<u64> power;
    unsigned int Base;
    const u64 MOD = (1UL << 61) - 1;
    const u64 POSITIVIZER = MOD * ((1UL << 3) - 1);
    const u64 MASK30 = (1UL << 30) - 1;
    const u64 MASK31 = (1UL << 31) - 1;
    const u64 MASK61 = MOD;
    // x:64bit, mod 2^61 - 1を返す
    u64 CalcMod(u64 x){
        u64 xu = x >> 61;
        u64 xd = x & MASK61;
        u64 res = xu + xd;
        if(res >= MOD) res -= MOD;
        return res;
    }
    // a * b をそのまま返す
    u64 Mul(u64 a, u64 b){
        u64 au = a >> 31;
        u64 ad = a & MASK31;
        u64 bu = b >> 31;
        u64 bd = b & MASK31;
        u64 mid = au * bd + bu * ad;
        u64 midu = mid >> 30;
        u64 midd = mid & MASK30;
        return ((au * bu) << 1) + midu + (midd << 31) + ad * bd;
    }
    u64 Mul(u64 a, unsigned int b){
        u64 au = a >> 31;
        unsigned int bd = b & MASK31;
        u64 middleBit= au * bd;
        return (a & MASK31) * bd + ((middleBit & MASK30) << 31) + (middleBit >> 30);
    }
public : 
    //[l, r)
    u64 get(int l, int r){return CalcMod(hash[r] + POSITIVIZER - Mul(hash[l], power[r - l]));}

    u64 merge(u64 l, u64 r, int lenr){return CalcMod(Mul(l, power[lenr]) + r);}

    u64 get_all(){ return get(0, n);}

    bool match(int l1, int r1, int l2, int r2){ return get(l1, r1) == get(l2, r2);}

    //[l1, r1), [l2, r2) の最長共通接尾辞
    int LCP(int l1, int r1, int l2, int r2){
        int len = std::min(r1 - l1, r2 - l2);
        int ok = 0, ng = len + 1;
        while(std::abs(ok - ng) > 1){
            int mid = (ok + ng) / 2;
            if(match(l1, l1 + mid, l2, l2 + mid)) ok = mid;
            else ng = mid;
        }
        return ok;
    }
};

