# jffah (Just For Fun And Humanity)

A modern C++ library implementing various data structures and algorithms for educational purposes and practical use.

## 🌟 Features

- **Data Structures**
  - Binary Search Trees
  - Merge Sort implementations
  - More coming soon...

- **Modern C++ Implementation**
  - Written in C++17
  - RAII-compliant memory management
  - Template-based generic implementations
  - Exception-safe operations

- **Educational Focus**
  - Clear, well-documented implementations
  - Example usage for each component
  - Performance analysis and comparisons

## 🚀 Getting Started

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, or MSVC 2017+)
- CMake 3.15 or higher
- Git (for cloning the repository)

### Building from Source

```bash
# Clone the repository
git clone https://github.com/yourusername/jffah.git
cd jffah

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
cmake --build .

# Run tests (optional)
ctest
```

## 📖 Usage Examples

### Binary Search Tree

```cpp
#include <jffah/trees/bst.hpp>

// Create a binary search tree
jffah::BST<int> tree;

// Insert elements
tree.insert(5);
tree.insert(3);
tree.insert(7);

// Search for a value
if (tree.find(3)) {
    std::cout << "Found 3!" << std::endl;
}

// Print tree in-order
tree.print_inorder(); // Output: 3 5 7
```

### Merge Sort

```cpp
#include <jffah/sorts/merge_sort.hpp>
#include <vector>

std::vector<int> data = {5, 2, 8, 1, 9};
jffah::merge_sort(data.begin(), data.end());
// data is now sorted: {1, 2, 5, 8, 9}
```

## 🗂️ Project Structure

```
jffah/
├── include/              # Public header files
│   └── jffah/
│       ├── trees/       # Tree data structures
│       └── sorts/       # Sorting algorithms
├── src/                 # Implementation files
├── tests/              # Unit tests
├── examples/           # Usage examples
└── docs/              # Documentation
```

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes, please open an issue first to discuss what you would like to change.

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 📞 Contact

If you have any questions or suggestions, please open an issue in the GitHub repository.

## ⭐ Show your support

Give a ⭐️ if this project helped you!
