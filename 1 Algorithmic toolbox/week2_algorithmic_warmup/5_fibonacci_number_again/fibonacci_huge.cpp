#include <iostream>
#include <cassert>

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % m;
    }

    return current % m;
}

int get_pisano_period(int m) {
    int previous = 0;
    int current  = 1;

    int i = 2;
    while(!(previous == 0 && current == 1) || i == 2){
        ++i;
        int tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % m;
    }

    return i - 2;
}

long long get_fibonacci_huge(long long n, long long m) {
    long long p = get_pisano_period(m);
    
    return get_fibonacci_huge_naive(n%p, m);
}

void test_solution() {    

    assert(get_fibonacci_huge(2015, 3) == 1);
    assert(get_fibonacci_huge(239, 1000) == 161);
    assert(get_fibonacci_huge(2816213588, 239) == 151);
    assert(get_fibonacci_huge(2015, 3) == get_fibonacci_huge_naive(2015, 3));

    for (int i = 1; i < 1500; ++i) {
        int n = rand() % 1000 + 1;
        int m = rand() % 1000;
        
        assert(get_fibonacci_huge(n, m) == get_fibonacci_huge_naive(n, m));
    }        
}


int main() {
    long long n, m;
    std::cin >> n >> m;
//    test_solution();
    std::cout << get_fibonacci_huge(n, m) << '\n';
}
