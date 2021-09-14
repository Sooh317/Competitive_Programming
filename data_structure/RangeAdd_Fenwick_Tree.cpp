template<class T> struct RangeAddBIT{
private:
    vector<T> a, b;
    int n;
public:
    RangeAddBIT(int _n):n(_n), a(_n + 2), b(_n + 2){}
    //[l, r)
    void add(int l, int r, T x = T(1)){
        ++l, ++r;
        for(int i = l; i <= n; i += i & -i) a[i] -= x * l;
		for(int i = l; i <= n; i += i & -i) b[i] += x;
		for(int i = r; i <= n; i += i & -i) a[i] += x * r;
		for(int i = r; i <= n; i += i & -i) b[i] -= x;
    }
    // [0, r)
    T sum(int r) {
		++r;
		T ret = 0;
		for(int x = r; x > 0; x -= x & -x) ret += a[x];
		for(int x = r; x > 0; x -= x & -x) ret += b[x] * r;
		return ret;
	}
    //[l, r)
    T sum(int l, int r){return sum(r) - sum(l);}
};
