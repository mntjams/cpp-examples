#include <vector>

std::vector<bool> get_vec() {
    std::vector<bool> vb{true, false, true, false};
    // Work with vb...
    return vb;
}

int main() {
    auto some_bool = get_vec()[2];
    // Using some_bool here would result in UB!!!

    // First look at what would happen if it was std::vector<int> instead.
    // get_vec would return std::vector<int>, operator[] for std::vector<int>
    // would return std::vector<int>::reference which is int& TODO - is it guaranteed to be int&?
    // and the deduced type from auto type deduction would be int... all good!

    // In this case, however, due to the required structure of std::vector<bool>
    // (stored as bits), the std::vector<bool> is (in most cases)
    // actually some object holding a pointer to a byte + offset in that byte.
    // This means that after the ;, the pointer dangles.

    // This can be fixed by explicitly casting the return value.
    auto some_bool_fixed = static_cast<bool>(get_vec()[2]);
    // or
    auto some_bool_fixed_better = bool{get_vec()[2]};
    // which may be even better as it prevents narrowing conversions.

    return 0;
}
