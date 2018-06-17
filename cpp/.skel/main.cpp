#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

using i64 = std::int64_t;

int read_int() {
    int result;
    if (std::scanf("%d", &result) != 1) {
        std::fputs("bad input", stderr);
        std::exit(1);
    }
    return result;
}

constexpr int solve(
        i64 const n,    // the number of prisoners
        i64 const m,    // the number of sweets
        i64 const s) {  // the chair number to start passing out treats at
    assert(0 < n);
    assert(0 < m);
    assert(0 < s && s <= n);
    auto const offset = m % n - 1;
    auto const index = ((s - 1) + offset + n) % n;
    return index + 1;
}

int main() {

    // Test with only one candy.
    auto const n = 6;
    for (auto s = 1; s <= n; ++s) {         // each starting seat
        assert(( solve(n, 1, s) == s ));
    }

    // Test with fewer candies than prisoners.
    assert(( solve(n, 2, 1) == 2 ));
    assert(( solve(n, 2, 2) == 3 ));
    assert(( solve(n, 2, 3) == 4 ));
    assert(( solve(n, 2, 4) == 5 ));
    assert(( solve(n, 2, 5) == 6 ));
    assert(( solve(n, 2, 6) == 1 ));

    // Test with just enough candies to go around.
    assert(( solve(n, n, 1) == 6 ));
    assert(( solve(n, n, 2) == 1 ));
    assert(( solve(n, n, 3) == 2 ));
    assert(( solve(n, n, 4) == 3 ));
    assert(( solve(n, n, 5) == 4 ));
    assert(( solve(n, n, 6) == 5 ));

    // Test with more than enough candies to go around.
    assert(( solve(n, n + 2, 1) == 2 ));
    assert(( solve(n, n + 2, 2) == 3 ));
    assert(( solve(n, n + 2, 3) == 4 ));
    assert(( solve(n, n + 2, 4) == 5 ));
    assert(( solve(n, n + 2, 5) == 6 ));
    assert(( solve(n, n + 2, 6) == 1 ));
    assert(( solve(n, n * 2, 1) == 6 ));
    assert(( solve(n, n * 2, 2) == 1 ));
    assert(( solve(n, n * 2, 3) == 2 ));
    assert(( solve(n, n * 2, 4) == 3 ));
    assert(( solve(n, n * 2, 5) == 4 ));
    assert(( solve(n, n * 2, 6) == 5 ));
    assert(( solve(n, n * 3 + 2, 1) == 2 ));
    assert(( solve(n, n * 3 + 2, 2) == 3 ));
    assert(( solve(n, n * 3 + 2, 3) == 4 ));
    assert(( solve(n, n * 3 + 2, 4) == 5 ));
    assert(( solve(n, n * 3 + 2, 5) == 6 ));
    assert(( solve(n, n * 3 + 2, 6) == 1 ));

    for (auto t = read_int(); t--;) {
        auto const n = read_int(), m = read_int(), s = read_int();
        std::printf("%d\n", solve(n, m, s));
    }
}
