// HW <= 16, 全探索解法
// verified : https://atcoder.jp/contests/abc196/submissions/27622900
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
dfs(dfs, 0, 0, a, b);
cout << ans << endl;

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

// HW <= 200(ちょっと厳しいかも), O(ABHW2^W)解法, タイルに個数制限あり
// verified : https://atcoder.jp/contests/abc196/submissions/27623476
if(h < w) swap(h, w);
V<V<V<int>>> dp(a + 1, V<V<int>>(b + 1, V<int>(1<<w)));
V<V<V<int>>> ndp(a + 1, V<V<int>>(b + 1, V<int>(1<<w)));
dp[0][0][0] = 1;
for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
        for(int aa = 0; aa <= a; aa++) for(int bb = 0; bb <= b; bb++) for(int mask = 0; mask < 1<<w; mask++){
            if(mask >> j & 1){ // 今見てるマスに置かれている
                ndp[aa][bb][mask ^ (1<<j)] += dp[aa][bb][mask];
            }
            else{ // 置かれていない
                if(bb < b) ndp[aa][bb + 1][mask] += dp[aa][bb][mask];
                if(aa < a){
                    if(j < w - 1 && ((mask >> (j + 1)) & 1) == 0){ // 1by2
                        ndp[aa + 1][bb][mask | (1<<(j+1))] += dp[aa][bb][mask];
                    }
                    if(i < h - 1){ // 2by1
                        ndp[aa + 1][bb][mask | (1<<j)] += dp[aa][bb][mask];
                    }
                }
            }
        }
        swap(dp, ndp);
    }
}
cout << dp[a][b][0] << endl;
