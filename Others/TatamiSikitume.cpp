// HW <= 16, 全探索解法
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

// HW <= 200, O(HW2^W)解法, タイルに個数制限なし
V<int> dp(1<<w);
dp[0] = 1;
for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
        V<int> ndp(1<<w);
        for(int mask = 0; mask < 1<<w; mask++){
            if(mask >> j & 1){ // 今見てるマスに置かれている
                ndp[mask ^ (1<<j)] += dp[mask];
            }
            else{ // 置かれていない
                ndp[mask] += dp[mask];
                if(j < w - 1 && ((mask >> (j + 1)) & 1) == 0){ // 1by2
                    ndp[mask | (1<<(j+1))] += dp[mask];
                }
                if(i < h - 1){ // 2by1
                    ndp[mask | (1<<j)] += dp[mask];
                }
            }
        }
        swap(dp, ndp);
    }
}
cout << dp[0] << endl;

// タイルに個数制限あり
