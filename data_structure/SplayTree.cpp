// verified : https://onlinejudge.u-aizu.ac.jp/solutions/problem/1508/review/6021403/sooh/C++17

template<typename T, T(*op)(T, T)>
struct SplayTree{
    struct Node{
        Node *left, *right, *parent;
        int size; // size of subtree
        T val, acc;

        Node(){
            left = right = parent = nullptr;
            size = 1;
        }
        int state(){
            if(!this->parent) return 0;
            if(this->parent->left == this) return 1;
            if(this->parent->right == this) return -1;
            return 0;
        }
        void rotate(){
            Node *pp, *p, *c;
            p = this->parent;
            pp = p->parent;
            if(p->left == this){
                c = this->right;
                this->right = p;
                p->left = c;
            }
            else{
                c = this->left;
                this->left = p;
                p->right = c;
            }
            if(pp){
                if(pp->left == p) pp->left = this;
                else pp->right = this;
            }
            this->parent = pp;
            p->parent = this;
            if(c) c->parent = p;
            p->update();
            this->update();
        }
        void splay(){
            while(this->state()){
                if(this->parent->state() == 0) this->rotate();
                else if(this->state() == this->parent->state()){
                    this->parent->rotate();
                    this->rotate();
                }
                else{
                    this->rotate();
                    this->rotate();
                }
            }
        }
        void update(){
            this->size = 1;
            this->acc = this->val;
            if(this->left) this->size += this->left->size, this->acc = op(this->acc, this->left->acc);
            if(this->right) this->size += this->right->size, this->acc = op(this->acc, this->right->acc);
        }
    };

    SplayTree(int n):cnt(0), N(n + 1){ // insertしていくパターン
        tree.resize(n + 1);
        for(int i = 0; i < n; i++){
            tree[i].parent = &tree[i + 1];
            tree[i + 1].left = &tree[i];
            tree[i].update();
        }
        root = &tree[n];
    }

    SplayTree(const std::vector<T> &a){ // 数列の操作を行うパターン
        int N = a.size();
        tree.resize(N);
        for(int i = 0; i < a.size(); i++){
            if(i + 1 < N){
                tree[i].parent = &tree[i + 1];
                tree[i + 1].left = &tree[i];
            }
            tree[i].val = a[i];
            tree[i].update();
        }
        root = &tree[N - 1];
    }
private:
    int N;
    int cnt = 0;
    Node* root;
    std::vector<Node> tree;

    Node* get(int x, Node* r){ // 左からx番目のnodeを根にして返す
        Node* cur = r;
        while(true){
            int lsize = cur->left ? cur->left->size : 0;
            if(x < lsize) cur = cur->left;
            else if(x == lsize){
                cur->splay();
                return cur;
            }
            else{
                cur = cur->right;
                x = x - lsize - 1;
            }
        }
    }

    Node* merge(Node* lroot, Node* rroot){
        if(!lroot) return rroot;
        if(!rroot) return lroot;
        lroot = get(lroot->size - 1, lroot);
        lroot->right = rroot;
        rroot->parent = lroot;
        lroot->update();
        return lroot;
    }

    pair<Node*, Node*> split(int left_num, Node* r){
        if(left_num == 0) return {nullptr, r};
        if(left_num == r->size) return {r, nullptr};
        r = get(left_num, r);
        Node* lr = r->left, *rr = r;
        rr->left = lr->parent = nullptr;
        rr->update();
        return {lr, rr};
    }

    Node* insert(int x, Node* node, Node* r){ // 左からx番目にnodeを挿入
        auto [lr, rr] = split(x, r);
        return merge(merge(lr, node), rr);
    }

    pair<Node*, Node*> erase(int x, Node* r){ // {消した後の木, 消したノード}
        r = get(x, r);
        Node* lr = r->left, *rr = r->right;
        if(lr) lr->parent = nullptr;
        if(rr) rr->parent = nullptr;
        r->left = r->right = nullptr;
        r->update();
        return {merge(lr, rr), r};
    }
    Node* shift(int l, int r, Node* root){ //数列用の操作[l, r]
        auto [lr, rr] = erase(r, root);
        root = lr;
        return insert(l, rr, root);
    }

    pair<Node*, T> query(int l, int r, Node* node){ // 数列用クエリ[l, r)
        Node *lr, *cr, *rr;
        auto tmp = split(r, node);
        rr = tmp.second;
        tmp = split(l, tmp.first);
        lr = tmp.first, cr = tmp.second;
        T ans = cr->acc;

        return {merge(merge(lr, cr), rr), ans};
    }

public:
    void shift(int l, int r){root = shift(l, r, root);}

    void update(int pos, T v){
        root = get(pos, root);
        root->val = v;
        root->update();
    }

    T query(int l, int r){
        auto tmp = query(l, r, root);
        root = tmp.first;
        return tmp.second;
    }
};
