#include "gtest/gtest.h"
#include "jffah/sorts/merge_sort.hpp"
#include <vector>
#include <algorithm> // For std::is_sorted

TEST(MergeSortTest, SortsVector) {
    std::vector<int> v = {5, 1, 4, 2, 8};
    jffah::merge_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(MergeSortTest, SortsEmptyVector) {
    std::vector<int> v;
    jffah::merge_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(MergeSortTest, SortsSingleElementVector) {
    std::vector<int> v = {42};
    jffah::merge_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(MergeSortTest, SortsAlreadySortedVector) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    jffah::merge_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(MergeSortTest, SortsReverseSortedVector) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    jffah::merge_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}
