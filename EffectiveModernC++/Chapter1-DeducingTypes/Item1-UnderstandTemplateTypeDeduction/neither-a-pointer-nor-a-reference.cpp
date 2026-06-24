/*
 * 1. If expr's type is a reference, ignore the reference part.
 * 2. Then, ignore all const and volatile qualifiers.
 */

template <typename T>
void f(T p) {}

int main() {
    int x = 1;
    const int cx = x;
    const int& crx = x;

    // In all stituations both ParamType and T are int
    f(x);
    f(cx);
    f(crx);

    // This makes sense as we COPY the argument.
    // The copy doesn't need to be marked const or volatile
    // ... because it is a copy.

    // NOTE the following interesting case.
    // Because we copy the pointer, it doesn't need to be const,
    // BUT it still points to a const int.
    const int* const cpcx = &x;

    f(cpcx);  // Both ParamType and T are const int*

    return 0;
}
