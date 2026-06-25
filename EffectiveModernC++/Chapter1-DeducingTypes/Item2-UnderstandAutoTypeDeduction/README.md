# Understand auto type deduction

_auto_ type deduction behaves exactly the same as template type deduction with only one exception.

Not counting this one exception, when a variable is declared using _auto_, _auto_ plays the role of _T_ in the template, and the type specifier for the variable acts as _ParamType_.

E.g.
```C++
int x = ...;
...
const auto& crx = x;
```
behaves the same as
```C++
template <typename T>
void func_for_crx(const T& p);
func_for_crx(x);
```

