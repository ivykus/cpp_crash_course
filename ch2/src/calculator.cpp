#include "calculator.h"

#include <iostream>

namespace Calc {
  int Calculator::operator()(int a, int b) {
    switch (op) {
    case Operation::ADD:
      return a + b;
    case Operation::SUBTRACT:
      return a - b;
    case Operation::Multiply:
      return a * b;
    case Operation::Devide:
      return a / b;
    default:
      std::cerr << "Unknown operation" << std::endl;
      return 0;
    }
  }
} // namespace Calc
