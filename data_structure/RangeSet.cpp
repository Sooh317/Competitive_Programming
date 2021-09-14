template<class T>
struct RangeSet{ // ranges are inclusive
private:
    const T TINF = numeric_limits<T>::max() >> 1;
    set<pair<T, T>> st;
public:
    RangeSet(){
        st.emplace(-TINF, -TINF);
        st.emplace(TINF, TINF);
    }
    int size(){return (int)st.size() - 2;}
    bool covered(const T l, const T r) {
		assert(l <= r);
		auto it = prev(st.upper_bound({l, TINF}));
		return it->first <= l && r <= it->second;
	}
    bool covered(const T x){return covered(x, x);}

    // if this segment is already included, the function returns false
    bool insert(T left, T right){
        assert(left <= right);
        auto itr = st.upper_bound({left, TINF});
        auto itl = prev(itr);
        auto [l, ml] = *itl;
        if(l <= left && right <= ml) return false;
        if(l <= left && left <= ml){
            left = l;
            st.erase(itl);
        }
        while(right > itr->second) itr = st.erase(itr);
        if(itr->first <= right){
            right = itr->second;
            st.erase(itr);
        }
        st.emplace(left, right);
        return true;
    }
    bool insert(T x){return insert(x, x);}

    // remove a segment of [left, right] from the current segments
    void erase(const T left, const T right){
        assert(left <= right);
        auto it = prev(st.upper_bound({left, TINF}));
        auto [l, r] = *it;
        if(l <= left && right <= r){
            if(l < left) st.emplace(l, left - 1);
            if(right < r) st.emplace(right + 1, r);
            st.erase(it);
            return;
        }
        if(l <= left && left <= r){
            if(l < left) st.emplace(l, left - 1);
            it = st.erase(it);
        }
        else it++;
        while(it->second <= right) it = st.erase(it);
        if(it->first <= right){
            st.emplace(right + 1, it->second);
            st.erase(it);
        }
        return;
    }

    void erase(const T x){erase(x, x);}

    // return mex that is greater than or equal to x
    T mex(const T x = 0) const{
        auto it = prev(st.upper_bound({x, TINF}));
        if(it->first <= x && x <= it->second) return it->second + 1;
        else return x;
    }

    void segments() const{
        for(auto &p : st){
            if(abs(p.first) == TINF) continue;
            cout << "[" << p.first << " " << p.second << "],"; 
        }
        cout << endl;
    }
};
