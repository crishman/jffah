#ifndef JFFMAH_MERGE_SORT_HPP
#define JFFMAH_MERGE_SORT_HPP

#include <vector>
#include <algorithm> // For std::merge and std::distance
#include <iterator>  // For std::iterator_traits

namespace jffah {

template <typename RandomIt>
void merge_sort(RandomIt first, RandomIt last) {
    using ValueType = typename std::iterator_traits<RandomIt>::value_type;
    auto const size = std::distance(first, last);

    if (size <= 1) {
        return;
    }

    auto middle = first + size / 2;

    merge_sort(first, middle);
    merge_sort(middle, last);

    std::vector<ValueType> temp_buffer;
    temp_buffer.reserve(size);

    std::merge(first, middle, middle, last, std::back_inserter(temp_buffer));
    std::copy(temp_buffer.begin(), temp_buffer.end(), first);
}

} // namespace jffah

#endif // JFFMAH_MERGE_SORT_HPP 