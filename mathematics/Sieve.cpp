struct Sieve {
    int MX;
    vector<bool> ip; // is prime
    vector<int> mu; // mobius
    vector<int> mf; // min factor
    Sieve(int _MX = 1000005, bool mobius = false):MX(_MX){
        ip.resize(MX, true);
        mf.resize(MX, 1);
        ip[0] = ip[1] = false;
        if(mobius){
            mu.resize(MX, 1);
            for(int i = 2; i < MX; i++){
                if(!ip[i]) continue;
                ip[i] = true;
                mf[i] = i;
                mu[i] = -1;
                for(int j = i+i; j < MX; j += i){
                    ip[j] = false;
                    if(mf[j] == 1) mf[j] = i;
                    if(j / i % i == 0) mu[j] = 0;
                    else mu[j] = -mu[j];
                }
            }
        }
        else{
            for(int i = 2; i < MX; i++){
                if(!ip[i]) continue;
                ip[i] = true;
                mf[i] = i;
                for(int j = i+i; j < MX; j += i){
                    ip[j] = false;
                    if(mf[j] == 1) mf[j] = i;
                }
            }
        }
    }

    vector<pair<int, int>> factorize(int n){
        assert(MX > n);
        std::vector<pair<int, int>> res;
        int p = mf[n], e = 0;
        while(n != 1){
            while(n % p == 0){
                n /= p;
                ++e;
            }
            res.emplace_back(p, e);
            p = mf[n], e = 0;
        }
        return res;
    }

    vector<int> divisors(int n){
        auto p = factorize(n);
        std::vector<int> res(1, 1);
        for(auto[v, k] : p){
            for(int i = res.size() - 1; i >= 0; i--){
                int c = 1;
                for(int j = 0; j < k; j++){
                    c *= v;
                    res.push_back(res[i] * c);
                }
            }
        }
        return res;
    }

    /* make 1-indexed vectors */
    // return F where F(i) = Σf(k) (i|k)
    template<class T> void fast_zeta(vector<T> &f){
        int N = f.size();
        for(int i = 2; i < N; i++){
            if(!ip[i]) continue;
            for(int j = (N - 1)/i; j >= 1; --j) f[j] += f[i*j];
        }
    }

    // return f where F(i) = Σf(k) (i|k)
    template<class T> void fast_mobius(vector<T> &F){
        int N = F.size();
        for(int i = 2; i < N; i++){
            if(!ip[i]) continue;
            for(int j = 1; j <= (N - 1)/i; ++j) F[j] -= F[i*j];
        }
    }

    // return h where h(k) = Σ f(i)*g(i) (gcd(i, j) = k) in O(NloglogN)
    template<class T> vector<T> gcd_convolution(const vector<T> &f, const vector<T> &g){
        int N = max(f.size(), g.size());
        vector<T> F(N), G(N), h(N);
        for(int i = 0; i < (int)f.size(); i++) F[i] = f[i];
        for(int i = 0; i < (int)g.size(); i++) G[i] = g[i];
        fast_zeta(F);
        fast_zeta(G);
        for(int i = 1; i < N; i++) h[i] = F[i] * G[i];
        fast_mobius(h);
        return h;
    }
};

