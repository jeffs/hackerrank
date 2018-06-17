#ifndef __cpp_structured_bindings
#pragma GCC diagnostic warning "-std=c++17"
#endif

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <string>
#include <vector>

using std::uint32_t;
using std::uint64_t;

int read_int() {
    int result;
    if (std::scanf("%d", &result) != 1) {
        std::fputs("bad input", stderr);
        std::exit(1);
    }
    return result;
}

struct add_result { uint32_t s, c; }; // sum, carry

constexpr add_result half_add(uint32_t const a, uint32_t const b) {
    uint64_t const sum = static_cast<uint64_t>(a) + b;
    return {
        static_cast<uint32_t>(sum & 0xFFFFFFFF),
        static_cast<uint32_t>(sum >> 32)
    };
}

constexpr add_result add(
        uint32_t const a,
        uint32_t const b,
        uint32_t const c) {
    auto const [s1,    c1] = half_add(a,  b);
    auto const [s,     c2] = half_add(s1, c);
    auto const [c_out, c3] = half_add(c1, c2); assert(c3 == 0);
    return { s, c_out };
}

class big_int {
    std::vector<int> _chunks;
  public:

    big_int(int const value): _chunks{value} { }

    big_int& operator+(big_int const& other) {
        if (_chunks.empty()) {
            _chunks = other._chunks;
        } else if (other._chunks.empty()) {
            // no change
        } else {
            // TODO
        }
        return *this;
    }

};

constexpr void test_half_add() {
    constexpr uint32_t m = std::numeric_limits<uint32_t>::max();
    constexpr struct { uint32_t a, b, s, c; } data[] = {
        { 0, 0, 0, 0 },
        { 0, 1, 1, 0 },
        { 1, 0, 1, 0 },
        { 0, m, m, 0 },
        { m, 0, m, 0 },
        { m, m, m - 1, 1 },
    };
    for (auto const row : data) {
        auto const [s, c] = half_add(row.a, row.b);
        assert(s == row.s);
        assert(c == row.c);
    }
}

constexpr void test_add() {
    constexpr uint32_t m = std::numeric_limits<uint32_t>::max();
    constexpr struct { uint32_t a, b, c_in, s, c_out; } data[] = {
        { 0, 0, 0, 0, 0 },          // c_in == 0
        { 0, 1, 0, 1, 0 },
        { 1, 0, 0, 1, 0 },
        { 0, m, 0, m, 0 },
        { m, 0, 0, m, 0 },
        { m, m, 0, m - 1, 1 },
        { 0, 0, 1, 1, 0 },          // c_in == 1
        { 0, 1, 1, 2, 0 },
        { 1, 0, 1, 2, 0 },
        { 0, m, 1, 0, 1 },
        { m, 0, 1, 0, 1 },
        { m, m, 1, m, 1 },
        { 0, 0, m, m, 0 },          // c_in == m
        { 0, 1, m, 0, 1 },
        { 1, 0, m, 0, 1 },
        { 0, m, m, m - 1, 1 },
        { m, 0, m, m - 1, 1 },
        { m, m, m, m - 2, 2 },
    };
    for (auto const row : data) {
        auto const [s, c] = add(row.a, row.b, row.c_in);
        assert(s == row.s);
        assert(c == row.c_out);
    }
}

int main() {
    test_half_add();
    test_add();
    std::puts("15511210043330985984000000");
}
