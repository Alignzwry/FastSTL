# FastSTL (In Progress)

**FastSTL** is a collection of optimized C++ headers, reimplementing and enhancing standard library containers and algorithms to achieve better performance in performance-critical applications. Each header in FastSTL is designed to replace its standard library counterpart with an emphasis on speed, memory efficiency, and improved functionality where possible.

## Table of Contents
- [Overview](#overview)
- [Installation](#installation)
- [Usage](#usage)
- [Available Headers](#available-headers)
- [Contributing](#contributing)
- [License](#license)

## Overview

The goal of **FastSTL** is to provide high-performance alternatives to commonly used C++ containers and utilities, such as `std::vector` and more.

## Installation

To use FastSTL, simply clone this repository and include the headers you need in your project.

```bash
git clone https://github.com/yourusername/FastSTL.git
```

Include FastSTL headers in your project as you would with standard library headers:
```cpp
#include "FastSTL/vector.hpp"
```

## Usage

FastSTL headers can be used as direct replacements for their standard library counterparts. For example:

```cpp
#include "FastSTL/vector.hpp"

int main() {
    fstl::vector<int> myVector;
    myVector.push_back(10);
    // Use as you would with std::vector
}
```

## Available Headers

### `FastSTL/vector.hpp`
An optimized version of `std::vector` with faster allocation strategies and improved performance on certain operations.

![image](https://github.com/user-attachments/assets/ee515ed3-73dd-49ba-b839-295c828998b6)

- **Pros**:
  - Reduced allocation overhead for frequent push/pop operations.
  - Faster speeds by removing unnecessary operations

- **Cons**:
  - Less functions as of now, emplace, insert for example are not working as of now
  - Less error handling
  - No resizing when vector gets smaller, you can use `fix_size()` to resize the vectors allocated memory to it's size

---

## Contributing

Contributions are welcome! If you have ideas for improvements or additional features, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
