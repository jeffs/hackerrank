#include <cstdio>
#include <cstdlib>

int read_int() {
    int result;
    if (std::scanf("%d", &result) != 1) {
        std::fputs("bad input", stderr);
        std::exit(1);
    }
    return result;
}

int main() {
    auto shared = 5, liked = 2, cumulative = 2;
    for (auto n = read_int(); --n;) {
        shared = liked * 3;
        liked = shared / 2;
        cumulative += liked;
    }
    std::printf("%d\n", cumulative);
}
