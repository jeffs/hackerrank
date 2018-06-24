#include <algorithm>
#include <cstdio>
#include <functional>
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
    std::vector<int> lengths(read_int());
    std::generate(lengths.begin(), lengths.end(), read_int);
    std::sort(lengths.begin(), lengths.end(), std::greater<>{});
    while (!lengths.empty()) {
        std::printf("%lu\n", lengths.size());
        auto const diff = [shortest = lengths.back()](int const length) {
            return length - shortest;
        };
        lengths.erase(
                std::find_if(lengths.rbegin(), lengths.rend(), diff).base(),
                lengths.end());
        std::transform(lengths.begin(), lengths.end(), lengths.begin(), diff);
    }
}
