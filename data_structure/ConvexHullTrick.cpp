// verified : https://atcoder.jp/contests/dp/submissions/26706424
// reference : https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h

struct Line{
    long long a, b; // ax + b
    mutable long long p; // 区間最小範囲の右端
    //bool operator<(const Line& o)const{return a < o.a;} // 最大値取得
    bool operator<(const Line& o)const{return a > o.a;} //最小値取得
    bool operator<(long long x)const{return p < x;}
};

struct ConvexHullTrick : std::multiset<Line, std::less<>>{
    static const long long INF = std::numeric_limits<long long>::max();
    long long div(long long a, long long b){return a/b - ((a^b)<0 && a%b);}
    // static const double INF = 1/.0;
    // double div(double a, double b){return a/b;}
    bool intersect(iterator x, iterator y){ // x->a < y->a and x and y are neighboring
        if(y == end()) return x->p = INF, false;
        if(x->a == y->a) x->p = x->b > y->b ? INF : -INF; 
        else x->p = div(y->b - x->b, x->a - y->a);
        return x->p >= y->p;
    }
    void add(long long n, long long m){ // add nx + m
        auto z = insert({n, m, 0}), y = z++, x = y;
        while(intersect(y, z)) z = erase(z);
        if(x != begin() && intersect(--x, y)) intersect(x, y = erase(y));
        while((y = x) != begin() && (--x)->p >= y->p) intersect(x, erase(y));
    }
    long long query(long long x){
        assert(!empty());
        auto it = *lower_bound(x);
        return it.a * x + it.b;
    }
};
