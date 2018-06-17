#include <cstdio>
#include <cstdlib>
#include <vector>

int read_int() {
    int result;
    if (std::scanf("%d", &result) != 1) {
        std::fputs("bad input", stderr);
        std::exit(1);
    }
    return result;
}

int main() {
    int const n = read_int();
    std::vector<int> q(n);  // inverse of p

    for (int i = 0; i < n; ++i) {
        q[read_int() - 1] = i;
    }

    for (int i = 0; i < n; ++i) {
        std::printf("%d\n", q[q[i]] + 1);
    }
}
