# Prefer auto to explicit type declarations

Using auto is preferred in most scenarios but it has two drawbacks.
One was already highlighted in Chapter 1 (auto deduces initializer list when used with `{}`).
The other is explained in Item 2.

TODO - Remove
Why is auto better than the explicit type decls?
1. Avoidance of uninitialized variables
2. Less verbose code
3. Some types cannot be represented without auto (lambdas)
    - And std::function is again more verbose and less performant
        - Possible heap allocation if closure doesn't fit inside object
        - Indirect calls -> no inlining
4. More type safety
    - std::vector<...>::size() has different size on 32b and 64b platform
    - auto adjusts itself accordingly
5. Possibly more performance
    - Creation of copies when looping over std::unordered_map elems
