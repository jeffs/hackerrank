#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

// Stores a set of unique values in descending order.  The behavior is
// undefined if more than 1,000 distinct values are inserted.
class flat_scoreboard {

    using array_type = std::array<unsigned, 1'000>;

    std::size_t _size = 0;
    array_type _values;

    auto lower_bound(unsigned const value) { 
        return std::lower_bound(begin(), end(), value, std::greater<>{});
    }

    // Note that this function does not maintain sort order.
    void push_back_invalid(unsigned const value) {
        assert(_size < capacity());
        _values[_size++] = value;
    };

  public:

    using iterator = array_type::iterator;
    using value_type = array_type::value_type;

    static constexpr std::size_t capacity() {
        return std::tuple_size<array_type>::value;
    }

    iterator begin() { return _values.begin(); }
    iterator end() { return begin() + _size; }

    // Inserts the specified `value` into this sequence if not already present.
    // Returns the index of the value in the sequence.
    std::size_t insert(value_type const value) {
        auto const bound = lower_bound(value);
        if (bound == end()) {
            push_back_invalid(value);
        } else if (*bound != value) {
            push_back_invalid(value);
            std::rotate(bound, bound + 1, end());
        }
        return bound - begin();
    }

    value_type front() const {
        assert(_size);
        return _values.front();
    }

    std::size_t size() const { return _size; }
};

struct scoreboard {

    using value_type = flat_scoreboard::value_type;

  private:
    std::vector<flat_scoreboard> _buckets;

    constexpr static value_type get_rung(value_type const value) {
        return value / flat_scoreboard::capacity();
    }

    static value_type get_rung(flat_scoreboard const& board) {
        return board.front() / flat_scoreboard::capacity();
    }

  public:

    std::size_t insert(value_type const value) {
        auto const rung = get_rung(value);
        auto const bound = std::lower_bound(
                _buckets.begin(), _buckets.end(),
                rung,
                [](flat_scoreboard const& board, value_type const rung) {
                    return get_rung(board) > rung;
                });
        auto const pos =
            bound ==_buckets.end() ? (
                    _buckets.emplace_back(),
                    _buckets.end() - 1)
          : get_rung(*bound) == rung ? bound
          : _buckets.insert(bound, {});
        auto const index_within_bucket = pos->insert(value);
        auto const count_before_bucket = std::accumulate(
                _buckets.begin(), pos,
                std::size_t{},
                [](std::size_t const count, flat_scoreboard const& bucket) {
                    return count + bucket.size();
                });
        return count_before_bucket + index_within_bucket;
    }
};

int main() {

    std::istream_iterator<unsigned> in(std::cin);

    scoreboard scores;
    for (auto n = *in++; n--;) {
        auto const value = *in++;
        scores.insert(value);
    }

    std::cerr << "Logging Output\n";

    for (auto m = *in++; m--;) {
        auto const place = scores.insert(*in++) + 1;
        std::cout << place << '\n';
    }
}
