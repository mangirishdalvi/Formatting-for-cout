## Synopsis

In C++ the `<iostream>` library is used to deal with I/O streams instead of something C's `printf`. Although `cout` is more type-safe, it is harder to read compared to C's `printf()`. This project is an attempt to get the best of both worlds i.e. use `cout` with format specifiers similar to `printf()`. Supports most of manipulators mentioned [here](http://en.cppreference.com/w/cpp/io/manip).

## Usage

We can use `Interpolate` along with `cout` as follows:

```c++
const char *str="John";
int num=45;
std::cout<<Interpolate("% is % years old",str,num)<<std::endl;
```

This will print out `John is 45 years old`.