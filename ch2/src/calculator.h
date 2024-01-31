#pragma once

namespace Calc {
enum class Operation { ADD, SUBTRACT, Multiply, Devide };

struct Calculator {
  const Operation op;
  Calculator(Operation op) : op(op) {}
  int operator()(int, int);
};

} // namespace Calc