// reference : https://ei1333.github.io/luzhiled/snippets/math/matrix.html
// gauss_jordan_F2 : https://atcoder.jp/contests/typical90/submissions/25903321
// gauss_jordan : unverified
// matrix exponentiation : verified in https://atcoder.jp/contests/abc129/tasks/abc129_f
template<class T>
struct Matrix{
    std::vector<std::vector<T>> A;

    Matrix(){}
    Matrix(int _n):A(_n, std::vector<T>(_n, 0)){}
    Matrix(int _n, int _m):A(_n, std::vector<T>(_m, 0)){}
    Matrix(std::vector<std::vector<T>> &_A){ A = _A;}

    int height()const{return A.size();}
    int width()const{return A[0].size();}

    void multiply_vector(std::vector<T> &v){
        assert(width() == v.size());
        std::vector<T> res(height());
        for(int i = 0; i < height(); i++){
            for(int j = 0; j < width(); j++){
                res[i] += (A[i][j] * v[j]);
                //res[i] += (A[i][j] * v[j]) % mod;
                //if(res[i] >= mod) res[i] -= mod;
            }
        }
        v.swap(res);
        return;
    }

    // the result will be in B
    int gauss_jordan_F2(Matrix &B){
        int rank = 0;
        B = Matrix(*this);
        int n = height(), m = width();
        for(int col = 0; col < m; col++){
            int idx = -1;
            for(int i = rank; i < n; i++){
                if(B[i][col] != 0){
                    swap(B[i], B[rank]);
                    break;
                }
            }
            if(B[rank][col] == 0) continue;
            for(int r = 0; r < n; r++){
                if(r == rank || B[r][col] == 0) continue;
                for(int c = m - 1; c > col; c--) B[r][c] ^= B[rank][c];
                B[r][col] = 0;
            }
            if(++rank == n) break;
        }
        return rank;
    }

    std::pair<int, int> gauss_jordan(Matrix &B){
        int rank = 0;
        T ret = 1;
        B = Matrix(*this);
        int n = height(), m = width();
        for(int col = 0; col < m; col++){
            int idx = -1;
            for(int i = rank; i < n; i++){
                if(B[i][col] != 0){
                    if(i != rank) ret *= -1;
                    swap(B[i], B[rank]);
                    break;
                }
            }
            if(B[rank][col] == 0) continue;
            ret *= B[rank][col];
            for(int j = m - 1; j >= col; j--) B[rank][j] /= B[rank][col];
            for(int r = 0; r < n; r++){
                if(r == rank || B[r][col] == 0) continue;
                for(int c = m - 1; c > col; c--) B[r][c] -= B[r][col] * B[rank][c];
                B[r][col] = 0;
            }
            if(++rank == n) break;
        }
        return std::pair<int, T>(rank, ret);
    }

    T det(){
        assert(height() == width());
        Matrix B;
        auto[rank, ret] = gauss_jordan(B);
        if(rank < height()) return T(0);
        return ret;
    }

    Matrix identity(int n){
        Matrix I(n);
        for(int i = 0; i < height(); i++) I[i][i] = 1;
        return I;
    }

    Matrix &operator+=(const Matrix &B){
        int n = height(), m = width();
        assert(n == B.height() && m == B.width());
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) (*this)[i][j] += B[i][j];
        return (*this);
    }
    Matrix &operator-=(const Matrix &B){
        int n = height(), m = width();
        assert(n == B.height() && m == B.width());
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) (*this)[i][j] -= B[i][j];
        return (*this);
    }
    Matrix &operator*=(const Matrix &B){
        int n = height(), m = width(), l = B.width();
        assert(m == B.height());
        std::vector<std::vector<T>> C(n, std::vector<T>(m, 0));
        for(int i = 0; i < n; i++) for(int j = 0; j < l; j++){
            for(int k = 0; k < m; k++){
                C[i][j] += ((*this)[i][k] * B[k][j]);
                //C[i][j] += ((*this)[i][k] * B[k][j]) % mod;
                //if(C[i][j] >= mod) C[i][j] -= mod;
            }
        }
        A.swap(C);
        return (*this);
    }
    Matrix &operator^=(long long k){
        Matrix B = Matrix::identity(height());
        while(k > 0){
            if(k & 1) B *= *this;
            *this *= *this;
            k >>= 1LL;
        }
        A.swap(B.A);
        return (*this);
    }
    Matrix operator+(const Matrix &B)const{
        return (Matrix(*this) += B);
    }

    Matrix operator-(const Matrix &B)const{
        return (Matrix(*this) -= B);
    }

    Matrix operator*(const Matrix &B)const{
        return (Matrix(*this) *= B);
    }
    Matrix operator^(const long long k)const{
        return (Matrix(*this) ^= k);
    }
    inline std::vector<T> &operator[](int k){ return A.at(k);}
    inline const std::vector<T> &operator[](int k)const{ return A.at(k);}

    friend ostream &operator<<(ostream &os, Matrix &p){
        size_t n = p.height(), m = p.width();
        for(int i = 0; i < n; i++) {
            os << "[";
            for(int j = 0; j < m; j++) {
                os << p[i][j] << (j + 1 == m ? "]\n" : ",");
            }
        }
        return (os);
    }
};
