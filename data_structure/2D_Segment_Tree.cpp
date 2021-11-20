// reference : https://atcoder.jp/contests/abc228/submissions/27369435
template <class S, S (*op)(S, S), S (*e)()> struct _2d_segtree {
	
	vector<segtree<S,op,e>> seg;
	
	_2d_segtree() : _2d_segtree(0, 0) {
	}
	/*
	compressed_2d_segtree(vector<long long> tx, vector<S> v){
		_tx = tx;
		seg = segtree<S,op,e>(v);
	}
	*/
	_2d_segtree(int h,int w){
		if(h>w){
			swap(h,w);
			F = true;
		}
		int n = h;
		log = 0;
		while((1LL<<log) < n){
			log++;
		}
		
		size = 1<<log;
		
		seg.resize(size*2, segtree<S,op,e>(w));
 
	}
	
	void set(int px, int py, S x) {
		if(F)swap(px,py);
		px += size;
		seg[px].set(py,x);
        for (int i = 1; i <= log; i++) update(px >> i, py);
    }
	
	S get(int px,int py) {
		if(F)swap(px,py);
		return seg[px+size].get(py);
    }
	
	S prod(int lx,int rx,int ly,int ry) {
		if(F){
			swap(lx,ly);
			swap(rx,ry);
		}
		S sml = e(), smr = e();
        lx += size;
        rx += size;
 
        while (lx < rx) {
            if (lx & 1) sml = op(sml, seg[lx++].prod(ly,ry));
            if (rx & 1) smr = op(seg[--rx].prod(ly,ry), smr);
            lx >>= 1;
            rx >>= 1;
        }
        return op(sml, smr);
    }
 
	S all_prod() { return seg[1].all_prod(); }
	int size, log;
	bool F = false;
	void update(int k, int py) {
		seg[k].set(py, op(seg[2*k].get(py), seg[2*k+1].get(py)));
	}
};
