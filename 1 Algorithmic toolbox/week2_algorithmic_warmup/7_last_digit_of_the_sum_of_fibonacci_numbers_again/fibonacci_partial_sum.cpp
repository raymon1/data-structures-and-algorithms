#include <iostream>
#include <vector>
#include <cassert>

using std::vector;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum = ( sum + current % 10);
        }

        long long new_current = next;
        next = (next + current) % 10;
        current = new_current;
    }

    return sum % 10;
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

long long get_fibonacci_huge(long long n, long long m) {
    long long p = get_pisano_period(m);
    
    return get_fibonacci_huge_naive(n%p, m);
}

long long get_fibonacci_partial_sum(long long from, long long to) {    
    return (get_fibonacci_huge(to + 2, 10) + 10 - get_fibonacci_huge(from + 1, 10)) % 10;
}

void test_solution() {
    for (int i = 1; i < 200; ++i) {
        int n = rand() % 700000 + 1;
        int m = rand() % n;
        int x = get_fibonacci_partial_sum(m, n);
        int y = get_fibonacci_partial_sum_naive(m, n);
     //   std::cout << x << " " << y << '\n';
        assert(x == y);
    }        
}


int main() {
    long long from, to;
    std::cin >> from >> to;
    
   // test_solution();
    std::cout << get_fibonacci_partial_sum(from, to) << '\n';
}
