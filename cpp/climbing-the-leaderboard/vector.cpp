#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

constexpr std::greater<> descending;

int main() {

    std::istream_iterator<unsigned> in(std::cin);

    std::vector<unsigned> scores;
    if (auto n = *in++) {
        for (scores.push_back(*in++); --n;) {
            auto score = *in++;
            if (scores.back() != score) {
                scores.push_back(score);
            }
        }
    }

    for (auto m = *in++; m--;) {
        auto const score = *in++;
        auto const first = begin(scores), last = end(scores);
        auto const place = std::lower_bound(first, last, score, descending);
        std::cout << (place - first + 1) << '\n';
        if (place == last || *place != score) {
            scores.insert(place, score);
        }
    }
}
