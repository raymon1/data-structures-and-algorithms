#include <iostream>
#include <cassert>

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;
        sum = (sum + current) % 10;
    }

    return sum % 10;
}

int fibonacci_sum(long long n) {
    if (n <= 1)
        return n;
    
    long long multiplier = n / 60;
    n = n % 60;
    
    return (fibonacci_sum_naive(n) + multiplier * fibonacci_sum_naive(60)) % 10;
}

void test_solution() {
    assert(fibonacci_sum(100) == 5);
    for (int n = 0; n < 10000; ++n)
        assert(fibonacci_sum(n) == fibonacci_sum_naive(n));
}

int main() {
    long long n = 0;
    std::cin >> n;
   // test_solution();
    
    std::cout << fibonacci_sum(n);
}
