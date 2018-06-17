#include <algorithm>
#include <cassert>
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

    auto const
        n = read_int(), // the number of elements in the integer array
        k = read_int(), // the rotation count
        q = read_int(); // the number of queries

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = read_int();
    }

    std::rotate(a.begin(), a.end() - k % a.size(), a.end());
    for (int i = 0; i < q; ++i) {
        auto const m = read_int();
        std::printf("%d\n", a[m]);
    }
}
