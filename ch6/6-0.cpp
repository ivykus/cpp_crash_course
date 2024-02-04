#include <concepts>
#include <iostream>
#include <stdexcept>

#include <cstddef>

template <typename T, typename U> T narrow_cast(U value) {
  T casted = static_cast<T>(value);
  U back = static_cast<U>(casted);
  if (back != value) {
    throw std::runtime_error("Narrowing conversion failed");
  }
  return casted;
}

template <typename T> struct SimpleUniquePointer {
  SimpleUniquePointer() = default;
  SimpleUniquePointer(T *ptr) : ptr{ptr} {}
  ~SimpleUniquePointer() {
    if (ptr) {
      delete ptr;
    }
  }
  SimpleUniquePointer(SimpleUniquePointer &other) = delete;
  SimpleUniquePointer &operator=(SimpleUniquePointer &other) = delete;

  SimpleUniquePointer(SimpleUniquePointer &&other) noexcept {
    if (this != &other) {
      ptr = other.ptr;
      other.ptr = nullptr;
    }
  }
  SimpleUniquePointer &operator=(SimpleUniquePointer &&other) noexcept {
    if (this != &other) {
      if (ptr) {
        delete ptr;
      }
      ptr = other.ptr;
      other.ptr = nullptr;
    }
    return *this;
  }
  T *get() { return ptr; }

private:
  T *ptr{};
};

struct Tracer {
  Tracer(const char *name) : name{name} {
    std::cout << "Tracer " << name << " created" << std::endl;
  }

  ~Tracer() { std::cout << "Tracer " << name << " destroyed" << std::endl; }

private:
  const char *name;
};

void consume_pointer(SimpleUniquePointer<Tracer> ptr) {
  std::cout << "Consuming pointer: " << ptr.get() << std::endl;
}

template <typename T>
concept Averagable =
    std::default_initializable<T> && requires(T a, T b, size_t size) {
      { a += b } -> std::same_as<T &>;
      { a / size } -> std::convertible_to<T>;
    };

template <Averagable T> T mean(T *a, size_t n) {
  T sum{};
  for (size_t i = 0; i < n; ++i) {
    sum += a[i];
  }
  return sum / n;
}

int main() {
#if 0
    int x = 600;
    int y = 330000;
    [[maybe_unused]] short xs, ys;
    try {
        xs = narrow_cast<short>(x);
        ys = narrow_cast<short>(y);
    } catch(const std::runtime_error& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    std::cout << xs << std::endl;
    std::cout << ys << std::endl;
#endif

#if 0
    SimpleUniquePointer<Tracer> ptr1{new Tracer{"ptr1"}};
    consume_pointer(std::move(ptr1));

    std::cout << "Pointer in main: " << ptr1.get() << std::endl;
#endif

#if 0
    int x[]{1, 2, 3, 4, 5};
    float y[]{1, 2.4, 33, 2.8};
    std::cout << mean(x, 5) << std::endl;
    std::cout << mean(y, 4) << std::endl;
    auto v1 = 1.1;
    auto v2 = 2.2;
    const double* values[] {&v1, &v2};
    //mean(values, 2);
#endif
}