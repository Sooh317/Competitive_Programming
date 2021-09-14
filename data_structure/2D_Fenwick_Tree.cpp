template<class T> struct BIT{
private:
    int _n1, _n2, cnt;
    vector<vector<T>> data2;
public:
    BIT(int n1, int n2) : _n1(n1), _n2(n2) {
        data2.resize(_n1);
        for(int i = 0; i < n1; i++) data2[i].resize(_n2, 0);
    };
    void add(int x, int y, T val){
        assert(0 <= x && x < _n1 && 0 <= y && y < _n2);
        x++, y++;
        for(int i = x; i <= _n1; i++){
            for(int j = y; j <= _n2; j++){
                data2[x - 1][y - 1] += val;
            }
        }
    }
    //[0, x][0, y]
    T sum(int x, int y){
        assert(0 <= x && x < _n1 && 0 <= y && y < _n2);
        T sum = 0;
        x++, y++;
        for(int i = x; i >= 0; i -= i & -i){
            for(int j = y; j >= 0; j -= j & -j){
                sum += data2[i][j];
            }
        }
        return sum;
    }
};
