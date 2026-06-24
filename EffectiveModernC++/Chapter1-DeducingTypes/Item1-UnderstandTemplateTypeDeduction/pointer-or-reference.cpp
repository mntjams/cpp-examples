/*
 * 1. If expr's type is a reference, ignore the reference part.
 * 2. Then pattern-match expr's type against ParamType to determine T.
 */

template <typename T>
void f(T& p) {}

template <typename T>
void cf(const T& p) {}

template <typename T>
void g(T* p) {}

int main() {
    int x = 1;
    const int cx = x;
    const int& crx = x;

    f(x);    // ParamType is int&, T is int
    f(cx);   // ParamType is const int&, T is const int
    f(crx);  // ParamType is const int&, T is const int

    // Now const is part of the ParamType, therefore T becomes just int
    cf(x);    // ParamType is const int&, T is int
    cf(cx);   // ParamType is const int&, T is int
    cf(crx);  // ParamType is const int&, T is int

    // With pointers, it works identically

    const int* cpx = &x;

    // "Taking address of" is not implicit as "taking reference of"
    // is, so we have to do it manually with &.
    g(&x);   // ParamType is int*, T is int
    g(&cx);  // ParamType is const int*, T is int

    g(cpx);  // ParamType is const int*, T is int

    // With ParamType const int*, it works analogously

    return 0;
};
