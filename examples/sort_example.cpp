#include <iostream>
#include <vector>
#include <algorithm> // For std::for_each
#include "jffah/sorts/merge_sort.hpp"

// Helper function to print vector elements
void print_vector(const std::vector<int>& vec) {
    for (int x : vec) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> data = {5, 1, 4, 2, 8, 0, 3, 9, 7, 6};

    std::cout << "Original vector: ";
    print_vector(data);

    jffah::merge_sort(data.begin(), data.end());

    std::cout << "Sorted vector:   ";
    print_vector(data);

    return 0;
} 