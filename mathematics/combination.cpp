struct Combination{
private:
    int N;
    const long long MOD;
    std::vector<long long> Fact;
    std::vector<long long> Finv;
    std::vector<long long> Inv;
public:
    Combination(int _N, int _MOD):N(_N), MOD(_MOD){
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
    long long comb(int n, int k){
        assert(n <= N);
        if(n < k || n < 0 || k < 0) return 0;
        return Fact[n] * Finv[k] % MOD * Finv[n - k] % MOD;
    }
    long long perm(int n, int k){
        assert(n <= N);
        if(n < k || n < 0 || k < 0) return 0;
        return Fact[n] * Finv[n - k] % MOD;
    }
    long long fact(int n){
        assert(0 <= n && n <= N);
        return Fact[n];
    }
    long long finv(int n){
        assert(0 <= n && n <= N);
        return Finv[n];
    }
    long long inv(int n){
        assert(0 < n && n <= N);
        return Inv[n];
    }
};

long long comb(int n, int k){
    if(n <= 0 || k < 0 || k > n) return 0;
    ll res = 1;
    for(int i = 1; i <= k; i++) res = res * (n - i + 1) / i;
    return res;
}
