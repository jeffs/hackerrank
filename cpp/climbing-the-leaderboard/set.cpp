#include <functional>
#include <iostream>
#include <iterator>
#include <set>

int main() {

    std::istream_iterator<unsigned> in(std::cin);

    std::set<unsigned, std::greater<>> scores;
    for (auto n = *in++; n--;) {
        scores.insert(*in++);
    }

    for (auto m = *in++; m--;) {
        auto const place = scores.insert(*in++).first;
        auto const index = std::distance(begin(scores), place);
        std::cout << (index + 1) << '\n';
    }
}
