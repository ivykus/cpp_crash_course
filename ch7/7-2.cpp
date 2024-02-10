// Create a LargeBucket class that can store up to 1MB of data. Extend the
// Heap class so it gives out a LargeBucket for allocations greater than 4096
// bytes. Make sure that you still throw std::bad_alloc whenever the Heap is
// unable to allocate an appropriately sized bucket.

#include <cstddef>
#include <iostream>
#include <new>

struct Bucket {
  const static size_t data_size{4096};
  std::byte data[data_size];
};

struct LargeBucket {
  const static size_t data_size{1024 * 1024};
  std::byte data[data_size];
};

struct Heap {
  void *allocate(size_t bytes) {
    if (bytes > LargeBucket::data_size) {
      throw std::bad_alloc{};
    }

    if (bytes > Bucket::data_size) {
      return allocate_large();
    }

    for (size_t i{}; i < n_heap_buckets; ++i) {
      if (!bucket_used[i]) {
        bucket_used[i] = true;
        return &buckets[i].data;
      }
    }
    throw std::bad_alloc{};
  }

  void *allocate_large() {
    std::cout << "Trying to allocate large \n";
    for (size_t i{}; i < n_heap_large_buckets; ++i) {
      if (!large_bucket_used[i]) {
        large_bucket_used[i] = true;
        return &large_buckets[i].data;
      }
    }
    throw std::bad_alloc{};
  }

  void free(void *p) {
    for (size_t i{}; i < n_heap_buckets; ++i) {
      if (&buckets[i].data == p) {
        bucket_used[i] = false;
        return;
      }
    }

    for (size_t i{}; i < n_heap_large_buckets; ++i) {
      if (&large_buckets[i].data == p) {
        large_bucket_used[i] = false;
        return;
      }
    }
  }

  static const size_t n_heap_buckets{10};
  Bucket buckets[n_heap_buckets]{};
  bool bucket_used[n_heap_buckets]{};

  LargeBucket large_buckets[n_heap_buckets]{};
  bool large_bucket_used[n_heap_buckets]{};
  static const size_t n_heap_large_buckets{5};
};

Heap heap;

void *operator new(size_t n_bytes) {
  std::cout << "Allocating \n";
  return heap.allocate(n_bytes);
}

void operator delete(void *p) {

  std::cout << "Freeing \n";
  heap.free(p);
}

struct testBigObject {
  const static size_t data_size{1024 * 8};
  char data[data_size]{};
};

int main() {
  testBigObject *p = new testBigObject{};
  delete p;
  try {
    while (true) {
      new char;
    }
  } catch (const std::bad_alloc &e) {
    std::cout << "Caught bad_alloc \n";
  }
}
