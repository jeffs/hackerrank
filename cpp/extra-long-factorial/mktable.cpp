#include <boost/multiprecision/cpp_int.hpp>

#include <iostream>

int main() {
    boost::multiprecision::cpp_int r = 1;
    for (int n = 1; n <= 100; ++n) {
        r *= n;
        std::cout << n << '\t' << r << '\n';
    }
}
