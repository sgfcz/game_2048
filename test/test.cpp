//
// Created by xiao on 25-5-30.
//

#include <iostream>
#include <string>

#include "unittest.h"
#include "src/CalculationBlock.h"

QTCPP2048_TEST_APP(QtCpp2048UnitTests)

QTCPP2048_ADD_TEST(Calculation, fourblock) {
  CalculationBlock block;
  std::vector a{0, 2, 0, 2};
  std::vector b{4, 0, 0, 0};

  auto c = block.ListCalculate(a);

  QTCPP2048_CHECK_EQUAL(b, c);
}
