#include <calculator.h>
#include <gtest/gtest.h>

TEST(Calculator_Test, BasicAssertions) {
  Calc::Calculator calcAdd{Calc::Operation::ADD};
  Calc::Calculator calcMultiply{Calc::Operation::Multiply};
  Calc::Calculator calcDevide{Calc::Operation::Devide};
  Calc::Calculator calcSubtract{Calc::Operation::SUBTRACT};

  EXPECT_EQ(calcAdd(1, 2), 3);
  EXPECT_EQ(calcMultiply(5, 10), 50);
  EXPECT_EQ(calcDevide(10, 2), 6);
  EXPECT_EQ(calcSubtract(10, 5), 5);
}