// verified : https://atcoder.jp/contests/practice2/submissions/29496999

#include <atcoder/modint>

struct NTT{
private:
    using mint = atcoder::modint998244353;
    std::vector<mint> root, inv_root;
    const mint pr;
    const int MAX = 23;

    void dft(std::vector<mint>& f, bool inverse, int log, int cnt = 23){
        if(f.size() == 1) return;
        int half = f.size() / 2;
        std::vector<mint> even(half), odd(half);
        for(int i = 0; i < half; i++) even[i] = f[2*i], odd[i] = f[2*i + 1];
        dft(even, inverse, log - 1, cnt - 1), dft(odd, inverse, log - 1, cnt - 1);
        mint now = 1;
        for(int i = 0; i < (int)f.size(); i++){
            f[i] = even[i % half] + now * odd[i % half];
            now *= (inverse ? inv_root[log] : root[log]);
        }
        return;
    }

public:
    NTT():root(24), inv_root(24), pr(3){
        root[23] = pr.pow(119), inv_root[23] = 1 / root[23];
        for(int i = MAX - 1; i >= 0; i--){
            root[i] = root[i + 1] * root[i + 1];
            inv_root[i] = inv_root[i + 1] * inv_root[i + 1];
        }
    }

    std::vector<mint> ntt(const std::vector<mint>& f, const std::vector<mint>& g){
        int log = 0, dim = 1;
        auto _f = f, _g = g;
        while(dim < f.size() + g.size() - 1) dim <<= 1, log++;
        assert(log <= 23);
        _f.resize(dim), _g.resize(dim);
        dft(_f, false, log), dft(_g, false, log);
        std::vector<mint> h(dim);
        for(int i = 0; i < dim; i++) h[i] = _f[i] * _g[i];
        dft(h, true, log);
        for(int i = 0; i < dim; i++) h[i] /= dim;
        return h;
    }
};
