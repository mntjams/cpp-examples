# Understand template type deduction

Pseudocode of a function template and its call:
```C++
template <typename T>
void f(ParamType param);

f(expr);
```

Type deduction is (expectedly) based on `expr` type but also on `ParamType`.
There are three cases:
1. `ParamType` is a pointer or a reference, but not universal reference.
2. `ParamType` is a universal reference.
3. `ParamType` is neither a pointer nor a reference.

Arrays and functions have interesting behavior in certain situations.
