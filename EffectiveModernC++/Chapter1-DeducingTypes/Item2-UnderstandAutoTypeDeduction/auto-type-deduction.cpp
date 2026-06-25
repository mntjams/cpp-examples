#include <initializer_list>

void do_something(int x, float y) {}

template <typename T>
void f(T p) {}

template <typename T>
void g(std::initializer_list<T> p) {}

int main() {
    // Cases 1 and 3 of template type deduction
    auto x = 1;
    auto& rx = x;
    const auto& crx = x;

    // Case 2 of template type deduction
    auto&& uref1 = x;
    auto&& uref2 = crx;
    auto&& uref3 = 1;

    // All the array/function situations also apply
    const char name[] = "Alyosha Karamazor";
    auto arr1 = name;
    auto& arr2 = name;

    auto fun1 = do_something;
    auto& fun2 = do_something;

    // The one special case where auto type deduction
    // behaves differently is when using uniform initialization.
    // The deduced type is std::initializer_list<T> for auto.
    // The same code fails to compile for template type deduction.
    auto x1 = 1;    // No uniform initialization, x1 is int
    auto x2(1);     // No uniform initialization, x2 is int
    auto x3 = {1};  // x3 is std::initializer_list<int>
    auto x4{1};     // Until C++17 x4 is std::initializer_list<int>
                    // This is highly unintuitive so in C++17
                    // the rules changed and x4 is deduced as int

    // Wouldn't compile
    // f({1});
    // You have to declare ParamType to be std::initializer_list<T>
    g({1});

    // Or you have to use this trick to deduce std::initializer_list
    // with auto type deduction and then pass it to f
    auto f_param = {1};
    f(f_param);

    // Lastly, the following example does not employ auto
    // type deduction even though the keyword auto is used.
    //
    // auto create_init_list() { return {1, 2, 3}; }
    //
    // This would therefore fail to compile.

    return 0;
}
