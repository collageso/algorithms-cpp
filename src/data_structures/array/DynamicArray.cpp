#include <algorithm>
#include <initializer_list>
#include <stdexcept>

/**
 * DynamicArray
 *
 * Differences from a fixed-size array:
 *
 * 1. **Dynamic Sizing**:
 *    - DynamicArray: Can grow or shrink in size as elements are added or
 * removed.
 *    - Fixed-size Array: Has a predetermined size that cannot be changed after
 * creation.
 *
 * 2. **Memory Management**:
 *    - DynamicArray: Allocates and deallocates memory as needed, providing
 * flexibility.
 *    - Fixed-size Array: Allocates a fixed amount of memory, potentially
 * wasting space if not fully utilized.
 *
 * 3. **Element Addition**:
 *    - DynamicArray: Supports adding elements beyond the initial capacity,
 * resizing as needed.
 *    - Fixed-size Array: Cannot accommodate more elements than its defined
 * size.
 *
 * 4. **Performance**:
 *    - DynamicArray: May incur overhead due to resizing operations, but is more
 * versatile.
 *    - Fixed-size Array: Generally faster for access and insertion when the
 * size is known and fixed.
 *
 */
template <typename T> class DynamicArray {
private:
  T *data;
  size_t size;
  size_t capacity;

  /**
   * Resize the array to a new capacity.
   *
   * @complexity
   * - Worst: O(n)
   * - Average: O(n)
   * - Best: O(n)
   */
  void resize(size_t new_capacity) {
    T *new_data = new T[new_capacity];

    for (size_t i = 0; i < size; ++i) {
      new_data[i] = std::move(data[i]);
    }

    delete[] data;
    data = new_data;
    capacity = new_capacity;
  }

public:
  /**
   * Default constructor.
   *
   * @complexity O(1)
   */
  DynamicArray() : size(0), capacity(1) { data = new T[capacity]; }

  /**
   * Constructor using an initializer list.
   *
   * @complexity O(n)
   */
  DynamicArray(std::initializer_list<T> init)
      : size(init.size()), capacity(init.size() * 2) {
    data = new T[capacity];
    std::copy(init.begin(), init.end(), data);
  }

  /**
   * Destructor.
   *
   * @complexity O(1)
   */
  ~DynamicArray() { delete[] data; }

  /**
   * Return size.
   *
   * @complexity O(1)
   */
  size_t getSize() { return size; }

  /**
   * Return Capacity.
   *
   * @complexity O(1)
   */
  size_t getCapacity() { return capacity; }

  /**
   * Access an element at a specific index.
   *
   * @complexity O(1)
   */
  const T &getAt(size_t index) const {
    if (index >= size) {
      throw std::out_of_range("Index out of range");
    }

    return data[index];
  }

  /**
   * Set the element at a specific index.
   *
   * @complexity O(1)
   */
  void setAt(size_t index, const T &value) {
    if (index >= size) {
      throw std::out_of_range("Index out of range");
    }

    data[index] = value;
  }

  /**
   * (Linear) Search for a value in the array.
   *
   * @complexity
   * - Worst: O(n) (If the value is at the last index or not present)
   * - Average: O(n)
   * - Best: O(1) (If the value is at the first index)
   */
  int find(const T &value) const {
    for (size_t i = 0; i < size; ++i) {
      if (data[i] == value) {
        return i;
      }
    }

    return -1;
  }

  /**
   * Insert an element at a specific index.
   *
   * @complexity
   * - Worst: O(n)
   * - Average: O(n)
   * - Best: O(1)
   */
  void insert(size_t index, const T &value) {
    if (index > size) {
      throw std::out_of_range("Index out of range");
    }

    if (index >= capacity) {
      resize(capacity * 2);
    }

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
