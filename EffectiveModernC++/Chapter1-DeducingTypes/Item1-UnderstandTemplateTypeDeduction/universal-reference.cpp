// Required for std::move
#include <utility>

/*
 * 1. If expr is lvalue, both ParamType and T are deduced to be lvalue
 * references.
 * 2. If expr is rvalue, the "normal" (Case 1) rules apply.
 */

template <typename T>
void f(T&& p) {}

// Function taking a single universal reference
// parameter can also look like this (C++20 required):
// void f(auto&& p);
// template <MyConcept T>
// void f(T&& p);
// void (MyConcept auto&& p);

int main() {
    int x = 1;
    const int cx = x;
    const int& crx = x;

    // NOTE - This is the only situation in template type
    // deduction where the deduced type is a reference!
    // It makes sense in the context of std::forward<T>
    f(x);    // ParamType is int&, T is int&
    f(cx);   // ParamType is const int&, T is const int&
    f(crx);  // ParamType is const int&, T is const int&

    // Same as in the normal scenario,
    // except we now have rvalue references (&&).
    // std::move is like a cast to rvalue.
    f(1);               // ParamType is int&&, T is int
    f(std::move(cx));   // ParamType is const int&&, T is const int
    f(std::move(crx));  // ParamType is const int&&, T is const int

    return 0;
}
