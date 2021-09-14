// can be used with vectors of any type
template <typename T> 
vector<int> Z_algorithm(const vector<T> &s){
    int N = s.size();
    vector<int> A(N);
    A[0] = N;
    // i is the current position and j is the range in consideration
    int i = 1, j = 0;
    while(i < N){
        while(i + j < N && s[j] == s[i + j]) j++;
        A[i] = j;
        if(j == 0){i++; continue;}
        int k = 1;
        while(k < j && k + A[k] < j){
            A[i + k] = A[k];
            k++;
        }
        i += k, j -= k;
    }
    return A;
}
