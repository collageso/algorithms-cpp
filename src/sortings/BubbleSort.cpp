#include <cstddef>
#include <utility>
#include <vector>

void bubbleSort(std::vector<int> &arr) {
  if (arr.empty()) {
    return;
  }

  size_t unsortedUntilIndex = arr.size() - 1;
  bool sorted = false;

  while (!sorted) {
    sorted = true;

    for (size_t i = 0; i < unsortedUntilIndex; ++i) {
      if (arr[i] > arr[i + 1]) {
        std::swap(arr[i], arr[i + 1]);
        sorted = false;
      }
    }

    --unsortedUntilIndex;
  }
}
