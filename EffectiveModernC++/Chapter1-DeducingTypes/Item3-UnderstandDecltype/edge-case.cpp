/*
 * As per this items README.md, decltype determines the declared type of a name
 * or the type and value category of an expression.
 *
 * Some seemingly innoccent expressions are lvalues and e.g. returning such
 * expressions from a function can invoke UB.
 */

decltype(auto) get_some_val() {
    auto some_val = 1;
    // Working with some_val...
    return (some_val);  // decltype((some_val)) is int& !!!
                        // This therefore returns a reference to
                        // a local variable.
};

// This is because wrapping a name in () creates an lvalue expression.
// The decltype rules for expressions state that the value category is also
// taken into account.

int main() { return 0; }
