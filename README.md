# elegant_exception

A lightweight and expressive C++ exception framework designed for modern error handling.  
Supports structured propagation, source location tracking, and monadic integration via `std::expected`.

## 📦 Features
- C++23 or above compilation
- Header-only design
- `elegant_exception` with error number, message and source location
- Seamless integration with `std::expected`
- Type-safe error propagation

## 🚀 Quick Start

```cpp
#include <elegant_exception/elegant_exception.h>
#include <iostream>

expected<int, elegant_exception> divide(int a, int b) 
{
    if (b == 0)
    {
        return unexpected{elegant_exception{"Division by zero"}};
    }
    
    return a / b;
}

int main() 
{
    divide(10, 0)
    .and_then([](int value)
    {
        std::cout << "Result: " << value << "\n";
        return expected<void, generic_exception>{};
    })
    .or_else([](const elegant_exception& eexp)
    {
        std::cerr << eexp.what() << std::endl;
        return std::unexpected{eexp};
    });
}
```


## 📁 Structure
include/
└── elegant_exception/
    └── elegant_exception.h

## 🧠 Philosophy
Minimal, expressive, and modern C++—designed for clarity and composability.

## 📜 License
MIT
This project is licensed under the [MIT License](https://mit-license.org/) — a permissive license that allows reuse with minimal restrictions.


## 👤 Author

**Rathnadhar K V**  
Passionate about modern C++ design, monadic error handling, and building elegant, dependency-light libraries.  
GitHub: [@rathnadhar](https://github.com/rathnadhar)



