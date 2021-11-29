struct RandomNumberGenerator{
    std::mt19937_64 mt;
    RandomNumberGenerator() : mt(std::chrono::steady_clock::now().time_since_epoch().count()) {}
    
    long long operator()(long long a, long long b) { // [a, b)
        std::uniform_int_distribution< long long > dist(a, b - 1);
        return dist(mt);
    }
    long long operator()(long long b) { // [0, b)
        return (*this)(0, b);
    }
};
