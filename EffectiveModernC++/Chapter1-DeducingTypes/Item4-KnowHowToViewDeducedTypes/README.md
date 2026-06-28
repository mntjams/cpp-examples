Just use
```C++
template <typename T>
class TD;
```
and view types as
```C++
TD<SomeType> t1;
TD<decltype(some_var)> t2;
```
