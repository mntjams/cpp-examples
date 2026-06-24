#include <cstddef>

/*
 * Arrays and functions decay to pointers in most cases.
 * This also holds for type deduction in pass-by-value
 * function templates.
 * But for pass-by-reference the actual array/function type is deduced.
 */

template <typename T>
class TD;

void do_something(int x, float y) {}

template <typename T>
void f(T p) {}

template <typename T>
void g(T& p) {}

template <typename T, std::size_t N>
constexpr std::size_t array_size(T (&)[N]) {
    return N;
}

int main() {
    const char name[] = "Alyosha Karamazov";

    // f(name);  // Both ParamType and T are const char*
    // g(name);  // ParamType is const char (&)[18], T is const char[18]

    // We can define a function that finds out array sizes at compile time.
    // This can be used to declare other arrays.
    char array_of_the_same_size[array_size(name)];

    f(do_something);  // Both ParamType and T are void (*)(int x, float y)
    g(do_something);  // ParamType is void (&)(int x, float y),
                      // T is void(int x, float y)

    return 0;
}
