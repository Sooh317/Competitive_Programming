// verified : https://atcoder.jp/contests/arc077/submissions/26038207
// using BIT

template<class T>
struct RangeAddLinearFunction{
private:
    int n;
    BIT<T> A, B;
public:
    RangeAddLinearFunction(int _n):n(_n){
        A = BIT<T>(n);
        B = BIT<T>(n);
    }

    // [l, r) <- +b, +(a+b), ...
    void add(int l, int r, T a, T b){
        assert(0 <= l && l <= r && r <= n);
        B.add(l, b - a*l);
        B.add(r, a*l - b);
        A.add(l, a);
        A.add(r, -a);
    }   

    T get(int x){
        assert(0 <= x && x < n);
        return A.sum(x + 1) * x + B.sum(x + 1);
    }

    void display(){
        for(int i = 0; i < n; i++) std::cerr << get(i) << " ";
        std::cerr << '\n';
    }
};
