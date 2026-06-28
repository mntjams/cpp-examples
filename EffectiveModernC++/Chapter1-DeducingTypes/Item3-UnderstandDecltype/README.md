# Understand decltype
`decltype` determines the _declared type of a name_ or the _type and value category of an expression_.
It behaves as expected most of the time. It has a special use-case for when the return type of a function is declared as _auto_. There are a few (probably) unexpected edge-cases to the `decltype` use-case.
