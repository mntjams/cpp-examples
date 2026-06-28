#include <vector>

/*
 * decltype does exactly what you expect it to do in most scenarios.
 */

class Widget;

struct Point {
    // decltype(Point::x) and decltype(Point::y) are int
    int x;
    int y;
};

template <typename T>
T& g(int idx);  // decltype(f<float>(1)) is float&

int main() {
    const int i = 0;          // decltype(i) is const int
    bool f(const Widget& w);  // decltype(f) is bool(const Widget&)
                              // decltype(f(w)) is bool
    std::vector<int> vi;      // decltype(vi) is std::vector<int>
    return 0;
}
