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

// HW <= 200, O(AHW2^W)解法, タイルに個数制限あり
// verified : https://atcoder.jp/contests/abc196/submissions/27623908
if(h < w) swap(h, w);
V<V<int>> dp(a + 1, V<int>(1<<w));
dp[0][0] = 1;
for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
        V<V<int>> ndp(a + 1, V<int>(1<<w));
        for(int aa = 0; aa <= a; aa++) for(int mask = 0; mask < 1<<w; mask++){
            if(mask >> j & 1){ // 今見てるマスに置かれている
                ndp[aa][mask ^ (1<<j)] += dp[aa][mask];
            }
            else{ // 置かれていない
                ndp[aa][mask] += dp[aa][mask];
                if(aa < a){
                    if(j < w - 1 && ((mask >> (j + 1)) & 1) == 0){ // 1by2
                        ndp[aa + 1][mask | (1<<(j+1))] += dp[aa][mask];
                    }
                    if(i < h - 1){ // 2by1
                        ndp[aa + 1][mask | (1<<j)] += dp[aa][mask];
                    }
                }
            }
        }
        swap(dp, ndp);
    }
}
cout << dp[a][0] << endl;

// H <= 6, W <= 1e12, 個数制限なし
// using Matrix.cpp, AtCoder/modint
// verified: https://atcoder.jp/contests/abc204/submissions/27625589
if(h < w) swap(h, w);
Matrix<mint> A(1<<w, 1<<w);
auto dfs = [&](auto&& self, int mask, int nmask, int x)->void{
    if(x == w){ // 埋め終わった
        A[nmask][mask]++;
        return;
    }
    if(mask >> x & 1){ // 何も埋められない
        self(self, mask, nmask, x + 1);
    }
    else{
        self(self, mask, nmask, x + 1); // 1by1
        self(self, mask, nmask | (1<<x), x + 1); // 2by1
        if(x + 1 < w && ((mask >> (x + 1)) & 1) == 0) self(self, mask, nmask, x + 2); // 1by2
        
    }
};
for(int mask = 0; mask < 1<<w; mask++) dfs(dfs, mask, 0, 0);
A ^= h;
V<mint> dp(1<<w);
dp[0] = 1;
A.multiply_vector(dp);
cout << dp[0].val() << endl;
