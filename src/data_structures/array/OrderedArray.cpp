#include <algorithm>
#include <stdexcept>

/**
 * OrderedArray
 *
 * This class provides functionality to manage an ordered array,
 *
 * Differences from a regular array:
 *
 * 1. **Sorted State**:
 *    - OrderedArray: Maintains a sorted order (ascending or descending).
 *    - Regular Array: No guaranteed order; elements can be in any sequence.
 *
 * 2. **Search Efficiency**:
 *    - OrderedArray: Supports binary search (O(log n)), making searches
 * efficient.
 *    - Regular Array: Requires linear search (O(n)), which is less efficient.
 *
 * 3. **Insertion Efficiency**:
 *    - OrderedArray: Inserting involves finding the position (binary search)
 * and shifting elements (O(n)).
 *    - Regular Array: Simple appending is O(1) if space is available, but can
 * be O(n) if resizing is needed.
 *
 */
template <typename T> class OrderedArray {
private:
  T *data;
  size_t size;
  size_t capacity;
  bool isAscending;

  /**
   * Resize the array to a new capacity.
   *
   * @complexity
   * - Worst: O(n)
   * - Average: O(n)
   * - Best: O(n)
   */
  void resize(size_t newCapacity) {
    T *newData = new T[newCapacity];

    for (size_t i = 0; i < size; ++i) {
      newData[i] = std::move(data[i]);
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
  }

  /**
   * Perform binary search to find the appropriate index for insertion.
   *
   * @complexity
   * - Worst: O(log n)
   * - Average: O(log n)
   * - Best: O(1)
   */
  int binarySearch(const T &value, bool isInsertion) const {
    size_t left = 0;
    size_t right = size - 1;

    while (left <= right) {
      size_t mid = left + (right - left) / 2;

      if (data[mid] == value) {
        return mid;
      } else if ((isAscending && data[mid] < value) ||
                 (!isAscending && data[mid] > value)) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    return isInsertion ? left : -1;
  }

public:
  /**
   * Default constructor with ascending order.
   *
   * @complexity O(1)
   */
  OrderedArray(bool ascending = true)
      : size(0), capacity(1), isAscending(ascending) {
    data = new T[capacity];
  }

  /**
   * Constructor using an initializer list.
   *
   * @complexity O(n log n)
   */
  OrderedArray(std::initializer_list<T> init, bool ascending = true)
      : size(init.size()), capacity(init.size() * 2), isAscending(ascending) {
    data = new T[capacity];
    std::copy(init.begin(), init.end(), data);
    std::sort(data, data + size, [this](const T &a, const T &b) {
      return isAscending ? a < b : a > b;
    });
  }

  /**
   * Destructor.
   *
   * @complexity O(1)
   */
  ~OrderedArray() { delete[] data; }

  /**
   * Return size.
   *
   * @complexity O(1)
   */
  size_t getSize() const { return size; }

  /**
   * Return Capacity.
   *
   * @complexity O(1)
   */
  size_t getCapacity() const { return capacity; }

  /**
   *
   * Access an element at a specific index.
   *
   * @complexity O(1)
   */

  const T &get(size_t index) const {
    if (index >= size) {
      throw std::out_of_range("Index out of range");
    }

    return data[index];
  }

  /**
   * Perform binary search on the ordered array.
   *
   * @complexity
   * - Worst: O(log n)
   * - Average: O(log n)
   * - Best: O(1)
   * @return index of the found element or -1 if not found.
   */
  int find(const T &value) const { return binarySearch(value, false); }

  /**
   * Insert an element while maintaining order using binary search.
   *
   * @complexity
   * - Worst: O(n)
   * - Average: O(n)
   * - Best: O(1)
   */
  void insert(const T &value) {
    if (size >= capacity) {
      resize(capacity * 2);
    }

    int index = binarySearch(value, true);

    for (size_t i = size; i > index; --i) {
      data[i] = std::move(data[i - 1]);
    }

    data[index] = value;
    ++size;
  }

  /**
   * Remove an element at a specific index.
   *
   * @complexity
   * - Worst: O(n)
   * - Average: O(n)
   * - Best: O(1)
   */
  void remove(size_t index) {
    if (index >= size) {
      throw std::out_of_range("Index out of range");
    }

    for (size_t i = index; i < size - 1; ++i) {
      data[i] = std::move(data[i + 1]);
    }

    --size;
  }

  // Begin iterator
  T *begin() { return data; }

  // End iterator
  T *end() { return data + size; }

  // Const begin iterator
  const T *begin() const { return data; }

  // Const end iterator
  const T *end() const { return data + size; }
};
