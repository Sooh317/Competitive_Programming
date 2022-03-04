// verified: https://atcoder.jp/contests/arc117/submissions/29836808

struct Lucas{
private:
    int p;
    std::vector<std::vector<int>> table;
    void init(){
        table[0][0] = 1;
        for(int i = 1; i < p; i++){
            table[i][0] = 1;
            for(int j = 1; j <= i; j++){
                table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % p;
            }
        }
    }
public:
    Lucas(int _p):p(_p), table(p, std::vector<int>(p)){
        assert(p <= 30000);
        init();
    }

    int comb(int n, int k){
        if(n <= 0 || n < k || k < 0) return 0;
        int res = 1;
        while(n){
            int ni = n % p, nk = k % p;
            n /= p, k /= p;
            res *= table[ni][nk];
            res %= p;
        }
        return res;
    }
};
