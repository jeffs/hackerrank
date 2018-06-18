#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

template <class T>
T read() {
    T value;
    if (!(std::cin >> value)) {
        std::cerr << "bad input\n";
        std::exit(1);
    }
    return value;
}

int common_prefix_length(std::string const& s, std::string const& t) {
    auto const b = s.begin();
    return std::mismatch(b, s.end(), t.begin(), t.end()).first - b;
}

bool transformable(std::string const& s, std::string const& t, int k) {
    auto const m = static_cast<int>(s.size());
    auto const n = static_cast<int>(t.size());
    if (m + n <= k) {
        // Can tear down one string and copy the other.
        return true;
    } else {
        int const c = common_prefix_length(s, t); 
        int const d = (s.size() - c) + (t.size() - c);
        return d <= k && (k - d) % 2 == 0;
    }
}

void test() {
    assert(( transformable("abc", "def", 6) ));
    assert(( transformable("hackerhappy", "hackerrank", 9) ));
}

int main() {
    test();
    auto const s = read<std::string>(), t = read<std::string>();
    auto const k = read<int>();
    std::cout << (transformable(s, t, k) ? "Yes" : "No") << '\n';
}
