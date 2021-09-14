// reference : https://github.com/NiMiLib/NoshiMochiLibrary/blob/queue_aggregation/lib/data_structure/sequence/queue_aggregation.hpp
// verified  : https://atcoder.jp/contests/typical90/submissions/25847908
template<class T, T(*op)(T, T)>
struct SWAG{
struct Node{
    T val, sum;
    Node(const T &val, const T &sum):val(val), sum(sum){}
};
private:
    std::stack<Node> L, R;
public:
    SWAG():L(), R(){}
    int size()const{return L.size() + R.size();}
    bool empty()const{ return L.empty() && R.empty();}
    T fold_all()const{
        assert(!empty());
        if(L.empty()) return R.top().sum;
        else if(R.empty()) return L.top().sum;
        return op(L.top().sum, R.top().sum);
    }
    void push(const T &x){
        if(R.empty()) R.emplace(x, x);
        else R.emplace(x, op(R.top().sum, x));
    }
    void pop(){
        assert(!empty());
        if(L.empty()){
            L.emplace(R.top().val, R.top().val);
            R.pop();
            while(!R.empty()){
                L.emplace(R.top().val, op(R.top().val, L.top().sum));
                R.pop();
            }
        }
        L.pop();
    }
    T top(){
        assert(!empty());
        if(L.empty()){
            L.emplace(R.top().val, R.top().val);
            R.pop();
            while(!R.empty()){
                L.emplace(R.top().val, op(R.top().val, L.top().sum));
                R.pop();
            }
        }
        return L.top().val;
    }
};
