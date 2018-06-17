#include <algorithm>    // lower_bound
#include <cstdio>       // printf, fputs, scanf
#include <cstdlib>      // exit
#include <deque>        // deque
#include <functional>   // greater

constexpr std::greater<> descending;

int read_int() {
    int result;
    if (std::scanf("%d", &result) != 1) {
        std::fputs("bad input", stderr);
        std::exit(1);
    }
    return result;
}

int main() {

    std::deque<int> scores;
    if (auto n = read_int()) {
        for (scores.push_back(read_int()); --n;) {
            auto const score = read_int();
            if (scores.back() != score) {
                scores.push_back(score);
            }
        }
    }

    for (auto m = read_int(); m--;) {
        auto const score = read_int();
        auto const first = begin(scores), last = end(scores);
        auto const place = std::lower_bound(first, last, score, descending);
        std::printf("%d\n", static_cast<int>(place - first + 1));
        if (place == last || *place != score) {
            scores.insert(place, score);
        }
    }
}
