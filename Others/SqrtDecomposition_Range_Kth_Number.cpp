// ###### UNVERIFIED ######

// kth number in increasing order
template<typename T>
struct Range_Kth_Number{ 
    int n, bsize, bnum, mx, mn;
    std::vector<T> A, B;

    Range_Kth_Number(const std::vector<T>& a):n(a.size()), A(a.begin(), a.end()), B(a.begin(), a.end()){
        mx = *std::max_element(B.begin(), B.end());
        mn = *std::min_element(B.begin(), B.end());
        bsize = (int)std::sqrt(n * std::log(n));
        bnum = n / bsize;
        for(int i = 0; i < bnum; i++) std::sort(B.begin() + i*bsize, B.begin() + (i+1)*bsize);
    }

    T query(int l, int r, int k){ // [l, r)
        T ok = mx, ng = mn - 1;
        while(ok - ng > 1){
            int pos = l, cnt = 0;
            T mid = (ok + ng) / 2;
            while(pos < r){
                if(pos % bsize || r - pos < bsize){
                    if(A[pos++] <= mid) cnt++;
                }
                else{
                    cnt += std::upper_bound(B.begin() + pos, B.begin() + pos + bsize, mid) - (B.begin() + pos);
                    pos += bsize;
                }
            }
            if(cnt >= k) ok = mid;
            else ng = mid;
        }
        return ok;
    }
};
