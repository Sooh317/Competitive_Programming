// reference: https://ei1333.github.io/luzhiled/snippets/structure/trie.html
// verified: https://atcoder.jp/contests/tenka1-2016-final-open/submissions/28028763

template<int char_kind = 26, int margin = 'a'>
struct Trie{
struct TrieNode{
    std::vector<int> ch, pattern;
    int chpat;
    TrieNode(){}
    TrieNode(int kind):chpat(0), ch(kind, -1){}
};
private:
    std::vector<TrieNode> nodes;

    void internal_add(const std::string& s, int idx, int node, int id){
        if(idx == (int)s.size()){
            nodes[node].pattern.emplace_back(id);
        }
        else{
            int c = s[idx] - margin;
            if(nodes[node].ch[c] == -1){
                nodes[node].ch[c] = (int)nodes.size();
                nodes.emplace_back(TrieNode(char_kind));
            }
            internal_add(s, idx + 1, nodes[node].ch[c], id);
        }
        nodes[node].chpat++;
    }

    void internal_query(const std::string& s, const function<void(int)>& f, int idx, int node){
        for(int id : nodes[node].pattern) f(id);
        if(idx == (int)s.size()) return;
        else{
            int c = s[idx] - margin;
            if(nodes[node].ch[c] == -1) return;
            internal_query(s, f, idx + 1, nodes[node].ch[c]);
        }
    }

public:
    Trie():nodes(1, TrieNode(char_kind)){}

    void add(const std::string& s){ internal_add(s, 0, 0, nodes[0].chpat);}
    void query(const std::string& s, const function<void(int)>& f, int i = 0){internal_query(s, f, i, 0);}
    int count()const{return nodes[0].chpat;}
    int size()const{return (int)nodes.size();}
};
