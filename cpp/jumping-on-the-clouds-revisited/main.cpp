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

struct sum_with_carry { std::uint32_t sum, carry; };

sum_with_carry add(uint32_t const first, uint32_t const second) {
    uint64_t const sum = static_cast<uint64_t>(first) + second;
    return {
        static_cast<uint32_t>(sum & 0xFFFFFFFF),
        static_cast<uint32_t>(sum >> 32),
    };
}

struct big_int {
    std::vector<int> _chunks;

    big_int(int const value): _chunks{value} { }

};

void test_add() {
    constexpr uint32_t m = std::numeric_limits<uint32_t>::max();
    constexpr struct { uint32_t u1, u2, sum, carry; } data[] = {
        { 0, 0, 0, 0 },
        { 0, 1, 1, 0 },
        { 1, 0, 1, 0 },
        { 0, m, m, 0 },
        { m, 0, m, 0 },
        { m, m, m - 1, 1 },
    };
    for (auto const row : data) {
        auto const result = add(row.u1, row.u2);
        assert(result.sum == row.sum);
        assert(result.carry == row.carry);
    }
}

int main() {

    test_add();
}
