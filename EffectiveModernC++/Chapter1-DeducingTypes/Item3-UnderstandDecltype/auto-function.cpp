/*
 * The auto keyword can also be used to
 * 1. declare function with trailing return type syntax or
 * 2. declare a function template.
 */

void authenticate_user() {};

// 1.
// This is just a different syntax for declaring functions.
// Its main advantage is that we can use the function
// parameters in the declaration of the returned type.
// This is usually done using decltype.
template <typename Container, typename Index>
auto auth_and_access_trailing(Container& c, Index i) -> decltype(c[i]) {
    authenticate_user();
    return c[i];
}

// 2.
// This is a syntax equivalent with
// template <typename T, typename Container, typename Index>
// T auth_and_access_template(Container& c, Index i) { ... };
// In other words, template type deduction takes place here, not
// auto type deduction.
//
// This also hints at a problem. Template type deduction will deduce
// a type returned BY VALUE (see Item1).
// The following would result in compilation error:
// std::vector<int> v{1, 2, 3};
// auth_and_access_template(v, 1)++;
//
// This is undesirable. To get the expected return type we
// have to use the decltype(auto) syntax instead of only auto.
template <typename Container, typename Index>
auto auth_and_access_template(Container& c, Index i) {
    authenticate_user();
    return c[i];
}

// This behaves as if we used decltype(c[i]) for the return type.
template <typename Container, typename Index>
decltype(auto) auth_and_access_template_fixed(Container& c, Index i) {
    authenticate_user();
    return c[i];
}

// decltype(auto) can also be used when declaring variables to get the correct
// value category of the type.
