#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>

// Stores a set of unique values in descending order.  The behavior is
// undefined if more than 1,000,000 distinct values are inserted.
class flat_scoreboard {
    std::size_t _size = 0;
    std::array<unsigned, 1'000'000> _values;

    auto lower_bound(unsigned const value) { 
        return std::lower_bound(begin(), end(), value, std::greater<>{});
    }

    // Note that this function does not maintain sort order.
    void push_back_invalid(unsigned const value) {
        assert(_size < _values.size());
        _values[_size++] = value;
    };

  public:

    using iterator = decltype(_values)::iterator;
    using value_type = decltype(_values)::value_type;

    iterator begin() { return _values.begin(); }
    iterator end() { return begin() + _size; }

    // Inserts the specified `value` into this sequence if not already present.
    // Returns the index of the value in the sequence.
    std::size_t insert(value_type const value) {
        auto const target = lower_bound(value);
        if (target == end()) {
            push_back_invalid(value);
        } else if (*target != value) {
            push_back_invalid(value);
            std::rotate(target, target + 1, end());
        }
        return target - begin();
    }
};

int main() {
    flat_scoreboard scores;
    std::istream_iterator<unsigned> i(std::cin);
    for (auto n = *i++; n--;) scores.insert(*i++);
    for (auto m = *i++; m--;) std::cout << (scores.insert(*i++) + 1) << '\n';
}
