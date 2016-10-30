Notice
======

The shortest integer swap function in C++ is probably the one below:

```
void swap_ints(int& a, int& b)
{
	a ^= b ^= a ^= b;
}
```

This is merely a condensed version of the `swap_opt` function presented in the
book.

While this looks clever, do not use this in production code. Instead, prefer
`std::swap` as it will (very likely) already be optimized for your target
architecture, while the XOR version above may not always be.
