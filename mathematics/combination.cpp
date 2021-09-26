// verified : https://atcoder.jp/contests/arc067/submissions/26109999
// verified : https://atcoder.jp/contests/arc067/submissions/26110000

struct Combination{
private:
    static const int N = 1000050;
    static const long long MOD = 1000000007;
    int _N, _MOD;
    std::vector<long long> Fact;
    std::vector<long long> Finv;
    std::vector<long long> Inv;
public:
    Combination(){
        Fact.resize(N + 1);
        Finv.resize(N + 1);
        Inv.resize(N + 1);
        Fact[0] = Fact[1] = 1;
        Finv[0] = Finv[1] = 1;
        Inv[1] = 1;
        for(int i = 2; i <= N; i++){
            Fact[i] = Fact[i - 1] * i % MOD;
            Inv[i] = MOD - Inv[MOD % i] * (MOD / i) % MOD;
            Finv[i] = Finv[i - 1] * Inv[i] % MOD;
        } 
    }
    Combination(int _n, int _mod):_N(_n), _MOD(_mod){
        Fact.resize(_N + 1);
        Finv.resize(_N + 1);
        Inv.resize(_N + 1);
        Fact[0] = Fact[1] = 1;
        Finv[0] = Finv[1] = 1;
        Inv[1] = 1;
        for(int i = 2; i <= _N; i++){
            Fact[i] = Fact[i - 1] * i % _MOD;
            Inv[i] = _MOD - Inv[_MOD % i] * (_MOD / i) % _MOD;
            Finv[i] = Finv[i - 1] * Inv[i] % _MOD;
        } 
    }
    long long comb(int n, int k){
        assert(n <= N);
        //assert(n <= _N);
        if(n < k || n < 0 || k < 0) return 0;
        return Fact[n] * Finv[k] % MOD * Finv[n - k] % MOD;
    }
    long long combk(int n, int k){
        if(n <= 0 || k < 0 || k > n) return 0;
        ll res = 1;
        for(int i = 1; i <= k; i++) res = res * (n - i + 1) / i;
        return res;
    }
    long long perm(int n, int k){
        assert(n <= N);
        //assert(n <= _N);
        if(n < k || n < 0 || k < 0) return 0;
        return Fact[n] * Finv[n - k] % MOD;
    }
    long long fact(int n){
        assert(0 <= n && n <= N);
        //assert(0 <= n && n <= _N);
        return Fact[n];
    }
    long long finv(int n){
        assert(0 <= n && n <= N);
        //assert(0 <= n && n <= _N);
        return Finv[n];
    }
    long long inv(int n){
        assert(0 < n && n <= N);
        //assert(0 <= n && n <= _N);
        return Inv[n];
    }
};
