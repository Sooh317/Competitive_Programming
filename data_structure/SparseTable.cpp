// verified : https://atcoder.jp/contests/abc189/submissions/25973202

template<typename T, T(*op)(T, T)>
struct SparseTable{
private:
    std::vector<std::vector<T>> table;
    std::vector<int> level;
public:
    SparseTable(const std::vector<T> &v){
        int log = 0;
        while((1<<log) <= v.size()) log++;
        table.assign(log, std::vector<T>(1<<log));
        for(int i = 0; i < (int)v.size(); i++) table[0][i] = v[i];
        for(int i = 1; i < log; i++){
            for(int j = 0; j + (1<<i) <= (1<<log); j++){
                table[i][j] = op(table[i - 1][j], table[i - 1][j + (1<<i-1)]);
            }
        }
        level.resize(v.size() + 1);
        for(int i = 2; i < (int)level.size(); i++) level[i] = level[i >> 1] + 1;
    }
    // [l, r)
    T prod(int l, int r){
        assert(l < r);
        int k = level[r - l];
        return op(table[k][l], table[k][r - (1<<k)]);
    }
};
