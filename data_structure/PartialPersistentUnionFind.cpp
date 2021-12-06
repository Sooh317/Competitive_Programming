// verified : https://atcoder.jp/contests/code-thanks-festival-2017/submissions/27736689
// verified : https://yukicoder.me/submissions/722421

struct Partially_Persistent_Union_Find{
private:
    // tree : {size of this tree (if this is root) / parent (otherwize), time when this node became a child}
    std::vector<std::pair<int, int>> tree;
    // siz : for recording the size of a tree at the time T
    std::vector<std::vector<std::pair<int, int>>> siz;
    int count;
public:
    Partially_Persistent_Union_Find(int n):
        tree(n, {1, std::numeric_limits<int>::max()}), 
        siz(n, std::vector<std::pair<int, int>>(1, {0, 1})), 
        count(0){}
    
    int leader(const int t, int x){
        while(tree[x].second <= t) x = tree[x].first;
        return x;
    }

    // you can get time/leader by changing the return value
    int merge(int x, int y){
        ++count;
        x = leader(count, x);
        y = leader(count, y);
        if(x == y) return count;
        if(tree[x].first < tree[y].first) std::swap(x, y);
        tree[x].first += tree[y].first;
        siz[x].emplace_back(count, tree[x].first);
        tree[y] = std::pair<int, int>(x, count);
        return count;
    }

    bool same(const int t, int x, int y){return leader(t, x) == leader(t, y);}

    int size(const int t, int x){
        x = leader(t, x);
        auto it = std::lower_bound(siz[x].begin(), siz[x].end(), std::pair<int, int>(t + 1, 0));
        return (--it)->second;
    }
};
