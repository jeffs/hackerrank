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

struct date { int day, month, year; };

constexpr int compute_fee(date const ret, date const due) {
    return  ret.year  < due.year  ?      0
        :   ret.year  > due.year  ? 10'000
        :   ret.month < due.month ?      0
        :   ret.month > due.month ?    500 * (ret.month - due.month)
        :   ret.day   > due.day   ?     15 * (ret.day   - due.day)
        :                                0;
}

int main() {
    date const
        ret{ read_int(), read_int(), read_int() },
        due{ read_int(), read_int(), read_int() };
    std::printf("%d\n", compute_fee(ret, due));
}
