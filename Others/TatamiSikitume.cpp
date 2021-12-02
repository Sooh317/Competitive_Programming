V<V<bool>> used(h, V<bool>(w));
int ans = 0;
auto dfs = [&](auto&& self, int x, int y, int ra, int rb)->void{
    if(x == h){ // 全部埋めた
        if(ra == 0 && rb == 0) ans++;
        return;
    }
    if(y == w){ //端に着いたら行を変える
        self(self, x + 1, 0, ra, rb);
        return;
    }
    if(used[x][y]){ // 既に埋まってるので隣へ
        self(self, x, y + 1, ra, rb);
        return;
    }
    if(rb){ // 1*1のマス
        used[x][y] = 1;
        self(self, x, y + 1, ra, rb - 1);
        used[x][y] = 0;
    }
    if(ra){ // 1*2 or 2*1 のマス
        if(y + 1 < w && !used[x][y + 1]){
            used[x][y] = used[x][y + 1] = 1;
            self(self, x, y + 1, ra - 1, rb);
            used[x][y] = used[x][y + 1] = 0;
        }  
        if(x + 1 < h){
            used[x][y] = used[x + 1][y] = 1;
            self(self, x, y + 1, ra - 1, rb);
            used[x][y] = used[x + 1][y] = 0;
        } 
    }
};
