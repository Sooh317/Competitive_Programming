// verified : https://atcoder.jp/contests/abc228/submissions/27894643
template <class S, S (*op)(S, S), S (*e)()>
struct Two_Demensional_Segtree{
private:
    int size, log;
	bool F = false;
	std::vector<atcoder::segtree<S,op,e>> seg; // seg[0] : None

	void init(int h,int w){
		if(h > w) std::swap(h,w), F = true;
		int n = h;
		log = 0;
		while(n > (1<<log)) log++;
		size = 1<<log; // number of leaves
        seg.resize(size*2, atcoder::segtree<S,op,e>(w));
	}

	void update(int k, int py){ seg[k].set(py, op(seg[2*k].get(py), seg[2*k+1].get(py)));}

public:
	Two_Demensional_Segtree(int h=0, int w=0){init(h, w);}
    Two_Demensional_Segtree(const std::vector<std::vector<S>>& a){
        int h = a.size(), w = a[0].size();
        init(h, w);
        for(int i = 0; i < h; i++) for(int j = 0; j < w; j++) set(i, j, a[i][j]);   
    }
	/*
	compressed_2d_segtree(vector<long long> tx, vector<S> v){
		_tx = tx;
		seg = segtree<S,op,e>(v);
	}
	*/
	S get(int px,int py){
		if(F) std::swap(px,py);
		return seg[px+size].get(py);
    }
	void set(int px, int py, S x){
		if(F) std::swap(px,py);
		px += size;
		seg[px].set(py,x);
        for (int i = 1; i <= log; i++) update(px >> i, py);
    }
	S prod(int lx,int rx,int ly,int ry){ // x方向[lx, rx), y方向[ly, ry)
		if(F) std::swap(lx,ly), std::swap(rx,ry);
		S sml = e(), smr = e();
        lx += size, rx += size;
        while (lx < rx) {
            if (lx & 1) sml = op(sml, seg[lx++].prod(ly,ry));
            if (rx & 1) smr = op(seg[--rx].prod(ly,ry), smr);
            lx >>= 1;
            rx >>= 1;
        }
        return op(sml, smr);
    }
	S all_prod(){return seg[1].all_prod();}
};
