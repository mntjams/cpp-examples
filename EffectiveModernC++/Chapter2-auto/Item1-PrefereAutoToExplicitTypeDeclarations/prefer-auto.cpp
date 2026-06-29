#include <print>
#include <unordered_map>
#include <utility>
#include <vector>

/*
 * Using auto helps us on several fronts as we:
 * 1. Avoid uninitialized variables,
 * 2. have to write less verbose code,
 * 3. can declare variables storing lambdas,
 * 4. increase type safety and
 * 5. possibly increase performance.
 */

// 1. The type of auto variables is deduced
// from the initializing expression.
// Leaving auto declared variable uninitialized is simply not possible.
int x;  // This is possible, x is uninitialized
// auto ax; // Not possible
auto ax{1};

// 2.
template <typename It>
void f(It b, It e) {
    while (b != e) {
        // Veeeery verbose!
        typename std::iterator_traits<It>::value_type vb = *b;
        // ...
        // Easier to just write
        auto avb = *b;
        // ...
    }
}

// 3. There is no other way to declare a lambda
auto lam = []() { return 5; };
// We could store it in std::function but this is again more verbose,
// it will lead to indirect function calls (no inlining) and may
// lead to heap allocation (if the lambda closure is big enough).

// 4. On 32b platform, the following code may work
// correctly for all possible returned values.
std::vector<int> v;
unsigned vs = v.size();
// However on a 64b platform v.size() will probably return
// some type whose value could undergo trunacation to fit
// into unsigned int => probably not expected.
auto avs = v.size();  // Much safer!

// 5.
class Widget {
   public:
    Widget() { std::println("Ctor"); }

    Widget(const Widget&) { std::println("Copy ctor"); }

    Widget(Widget&&) { std::println("Move ctor"); }

    Widget& operator=(const Widget&) {
        std::println("Copy assgn");
        return *this;
    }

    Widget& operator=(Widget&&) {
        std::println("Move assgn");
        return *this;
    }

    // Required to use Widget as a key in unordered_map
    bool operator==(const Widget&) const { return false; }
};

// Required to use Widget as a key in unordered_map
namespace std {
template <>
struct hash<Widget> {
    std::size_t operator()(const Widget&) const {
        // Arbitrary number, we just need it to compile
        return 1;
    }
};
}  // namespace std

int main() {
    std::println("Constructing unordered_map");
    std::unordered_map<Widget, int> m;
    m.emplace(Widget{}, 1);
    m.emplace(Widget{}, 2);
    m.emplace(Widget{}, 3);
    m.emplace(Widget{}, 4);
    std::println("unordered_map constructed");
    std::println();

    std::println("Looping without auto");
    // ...
    for (const std::pair<Widget, int>& p : m) {
        std::println("{}", p.second);
        // Do something
    }
    std::println();
    // This, however, instantiates a temporary object in every iteration.
    // The correct type for a key/value pair in std::unordered_map<K, V> is
    // std::pair<const K, V>.
    // Our declared type is however std::pair<K, V> (no const!).
    // The compiler will try to convert std::pair<const K, V> to std::pair<K, V>
    // and it will succeed by copying the std::pair<const K, V> into a temporary
    // of type std::pair<K, V> and binding our reference to said temporary.

    // Using auto prevents such mistakes
    std::println("Looping with auto");
    for (const auto& p : m) {
        std::println("{}", p.second);
        // Do something
    }
    return 0;
}
