// verified : https://atcoder.jp/contests/abc196/submissions/25975253

template<typename T>
struct Clamp{
    T L, R, base;
    bool horizontal;
    T line;

    Clamp():L(std::numeric_limits<T>::min()), R(std::numeric_limits<T>::max()), base(0), horizontal(false){}

    // f(x) <- f(x) + a
    void compose_add(T a){
        if(horizontal) line += a;
        else base += a;
    }

    // f(x) <- min(f(x), a)
    void compose_min(T a){
        if(horizontal){
            line = std::min(line, a);
            return;
        }
        T p = a - base;
        if(p <= L) line = a, horizontal = true;
        else if(p < R) R = p;
    }
    // f(x) <- max(f(x), a)
    void compose_max(T a){
        if(horizontal){
            line = std::max(line, a);
            return;
        }
        T p = a - base;
        if(p >= R) line = a, horizontal = true;
        else if(L < p) L = p;
    }
    // f(x)
    inline const T operator[](T k) {return (horizontal ? line : std::min(std::max(k, L), R) + base);}
};
