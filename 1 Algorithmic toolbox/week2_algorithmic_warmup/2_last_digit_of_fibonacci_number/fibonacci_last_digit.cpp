#include <iostream>
#include <cassert>

long long get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

long long get_fibonacci_last_digit(int n) {
    return get_fibonacci_last_digit_naive(n % 60);
}

void test_solution() {
    assert(get_fibonacci_last_digit(3) == 2);
    assert(get_fibonacci_last_digit(10) == 5);
    for (int n = 0; n < 100; ++n) {
        std::cout << n << ' ' << get_fibonacci_last_digit_naive(n) << '\n';
        assert(get_fibonacci_last_digit(n) == get_fibonacci_last_digit_naive(n));
    }
        
}


int main() {
    int n;
    std::cin >> n;
 //   test_solution();
    
    long long  c = get_fibonacci_last_digit(n);
    std::cout << c << '\n';
}
