# sb
Sb: String builder for C

The C language's string handling infrastructure is error-prone.
Fixed-sized buffer, buffer overflows, and missing string termination nulls
lead to buggy software.
"Sb" is inspired by Java's string builder object.

The goals of "sb" are:
* Lightweight.
Low complexity, small size.
* Not a Borg.
"Sb" co-exists with other string handling methodologies in the same codebase.
* Dynamic sizing.
"Sb" will grow its internal buffer to meet demand.
* Consistent error handling.
Uses "err" (see [err repository](https://github.com/fordsfords/err)).
