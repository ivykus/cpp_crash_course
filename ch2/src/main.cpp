#include "calculator.h"
#include <iostream>

int main() {
  using namespace Calc;
  Calculator calcAdder{Operation::ADD};
  std::cout << calcAdder(1, 2) << std::endl;

  Calculator calcMultiplier{Operation::Multiply};
  std::cout << calcMultiplier(1, 2) << std::endl;
  return 0;
}