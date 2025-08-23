# elegant_exception

A lightweight and expressive C++ exception framework designed for modern error handling.  
Supports structured propagation, source location tracking, and monadic integration via `std::expected`.

## 📦 Features
1. C++23 or above compilation
2. Header-only design
3. `elegant_exception` with error number, message and source location
4. Seamless integration with `std::expected`
5. Type-safe error propagation
6. `raise()` — a symbolic alias for exception creation, with source location fidelity
7. `make_exception` — meta-aware helper adapting to debug/release builds

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

With raise()

#include <elegant_exception/elegant_exception.h>
#include <iostream>

using elegant_exception::raise;

expected<int, elegant_exception> divide(int a, int b) 
{
    if (b == 0)
    {
        return unexpected{raise(1001, "Division by zero")};
    }
    
    return a / b;
}
```


## 📁 Structure
include/
└── elegant_exception/
    └── elegant_exception.h
    
## 🧪 Build Instructions

## 🔧 Configure with Ninja

cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release

## 🛠 Build
cmake --build build

## 📦 Install
sudo cmake --install build


## 🧠 Philosophy
1. Minimal, expressive, and modern C++—designed for clarity and composability.
2. Exception creation is ritualized via `raise()`, reflecting intentional design.
3. Debug builds retain source location for auditability; release builds remain lean.

## 📜 License
MIT
This project is licensed under the [MIT License](https://mit-license.org/) — a permissive license that allows reuse with minimal restrictions.


## 👤 Author

**Rathnadhar K V**  
Passionate about modern C++ design, monadic error handling, and building elegant, dependency-light libraries.  
GitHub: [@rathnadhar](https://github.com/rathnadhar)

## 📜 Changelog

<details>
<summary>Click to expand</summary>

### v3 — 2025‑08‑23
1. Fixed compilation errors.
2. Added .gitignore
3. 🔐 All artifacts now signed with GPG key '5A4A40D85A0C1D11' and provenance verified.


### v2 — 2025‑06‑14
### Added
1. `raise()` — symbolic alias for exception creation with source location fidelity
2. `make_exception` — build-aware helper adapting to debug/release modes

### Updated
1. README.md to reflect new invocation patterns and philosophy
2. LICENSE clarified for reuse and attribution

### v1 — 2025‑04‑01
1. Initial public release of elegant_exception. A new C++23 paradignm for universal exception engine.

</details>
