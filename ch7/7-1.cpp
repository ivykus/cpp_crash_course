// 7-1. Create an UnsignedBigInteger class that can handle numbers bigger than
// a long. You can use a byte array as the internal representation (for example,
// uint8_t[] or char[]). Implement operator overloads for operator+ and
// operator-. Perform runtime checks for overflow. For the intrepid, also
// implement operator*, operator/, and operator%. Make sure that your operator
// overloads work for both int types and UnsignedBigInteger types. Implement an
// operator int type conversion. Perform a runtime check if narrowing would
// occur.
#include <climits>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <iostream>
#include <string_view>
#include <vector>

class UnsignedBigInteger {
private:
  std::vector<uint8_t> data;

public:
  UnsignedBigInteger() {}

  explicit UnsignedBigInteger(long n) {
    if (n < 0) {
      throw std::bad_alloc{};
    }
    while (n > 0) {
      data.push_back(n & 0xff);
      n >>= 8;
    }
  }

  UnsignedBigInteger(std::string_view sw) { std::cout << sw << std::endl; }

  UnsignedBigInteger operator+(const UnsignedBigInteger &other) {
    UnsignedBigInteger result;
    size_t i{0}, j{0};
    int carry{0};
    while (i < data.size() && j < other.data.size()) {

      auto sum = carry + data[i] + other.data[j];
      result.data.push_back(sum & 0xff);
      carry = sum >> CHAR_BIT;

      i++;
      j++;
    }

    while (i < data.size()) {
      auto sum = carry + data[i++];
      result.data.push_back(sum & 0xff);
      carry = sum >> CHAR_BIT;
    }

    while (j < other.data.size()) {
      auto sum = carry + other.data[j++];
      result.data.push_back(sum & 0xff);
      carry = sum >> CHAR_BIT;
    }
    return result;
  }

  UnsignedBigInteger operator-(const UnsignedBigInteger &other) {
    if (other.data.size() > data.size()) {
      throw std::logic_error{"undefined behaviour in operator-: left"
                             "operand is smaller than right operand"};
    }

    UnsignedBigInteger result;
    size_t i{0}, j{0};
    int borrowed{0};
    while (i < data.size() && j < other.data.size()) {

      auto sum = data[i] - other.data[j] - borrowed;
      if (sum < 0) {
        sum += 256;
        borrowed = 1;
      } else {
        borrowed = 0;
      }
      result.data.push_back(sum & 0xff);
      i++;
      j++;
    }

    while (i < data.size()) {
      auto sum = data[i++] - borrowed;
      if (sum < 0) {
        sum += 256;
        borrowed = 1;
      } else {
        borrowed = 0;
      }
      result.data.push_back(sum & 0xff);
    }
    return result;
  }

  UnsignedBigInteger operator*(const UnsignedBigInteger &other) {
    UnsignedBigInteger result;
    std::vector<u_int16_t> temp(data.size() + other.data.size());

    for (size_t i{}; i < data.size(); ++i) {
      for (size_t j{}; j < other.data.size(); ++j) {
        temp[i + j] += data[i] * other.data[j];
      }
    }

    for (size_t i{}; i < temp.size(); ++i) {
      result.data.push_back(temp[i] & 0xff);
      if (i + 1 < temp.size())
        temp[i + 1] += temp[i] >> CHAR_BIT;
      else if (temp[i] >> CHAR_BIT) {
        result.data.push_back(temp[i] >> CHAR_BIT);
      }
    }
    return result;
  }

  UnsignedBigInteger operator/(const UnsignedBigInteger &other) {
    // TODO: implement
    throw std::logic_error{"unemplemented"};

    UnsignedBigInteger result;
    return result;
  }

  UnsignedBigInteger operator%(const UnsignedBigInteger &other) {
    // TODO: implement
    throw std::logic_error{"unemplemented"};
    UnsignedBigInteger result;
    return result;
  }

  explicit operator int() const {
    if (data.size() > sizeof(int)) {
      throw std::overflow_error("Narrowing");
    }
    int result = 0;
    for (size_t i = 0; i < data.size(); ++i) {
      result += (static_cast<int>(data[i]) << (i * CHAR_BIT));
    }
    return result;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const UnsignedBigInteger &ubi);
};

std::ostream &operator<<(std::ostream &os, const UnsignedBigInteger &ubi) {
  for (const auto &ch : ubi.data) {
    os << std::hex << static_cast<int>(ch) << ' ';
  }
  return os;
}

int main() {
  UnsignedBigInteger ubi{5000};
  UnsignedBigInteger ubi2{100000};
  std::cout << static_cast<int>(ubi + ubi2) << std::endl;
  std::cout << static_cast<int>(ubi2 - ubi) << std::endl;

  UnsignedBigInteger ubi3{625};
  UnsignedBigInteger ubi4{899};
  std::cout << static_cast<int>(ubi3 * ubi4) << std::endl;
}