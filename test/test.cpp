//
// Created by xiao on 25-5-30.
//

#include <iostream>
#include <string>
#include <cstdint>

#include "unittest.h"
#include "src/CalculationBlock.h"

QTCPP2048_TEST_APP(QtCpp2048UnitTests)

QTCPP2048_ADD_TEST(Calculation, fourblock) {
  CalculationBlock block;
  std::vector<int32_t> a{0, 2, 0, 2};
  std::vector<int32_t> b{4, 0, 0, 0};

  auto c = block.ListCalculate(a);

  QTCPP2048_CHECK_EQUAL(b, c);
}

QTCPP2048_ADD_TEST(Calculation, left_move) {
  CalculationBlock block;
  std::vector<int32_t> board{2, 0, 2, 4, 0, 4, 0, 4, 2, 2, 2, 0, 0, 0, 0, 0};
  std::vector<int32_t> expected{4, 4, 0, 0, 8, 0, 0, 0, 4, 2, 0, 0, 0, 0, 0, 0};

  auto moved = block.CalculateLeftMove(board);

  QTCPP2048_CHECK_ASSERT(moved);
  QTCPP2048_CHECK_EQUAL(board, expected);
}

QTCPP2048_ADD_TEST(Calculation, right_move) {
  CalculationBlock block;
  std::vector<int32_t> board{2, 0, 2, 4, 0, 4, 0, 4, 2, 2, 2, 0, 0, 0, 0, 0};
  std::vector<int32_t> expected{0, 0, 4, 4, 0, 0, 0, 8, 0, 0, 2, 4, 0, 0, 0, 0};

  auto moved = block.CalculateRightMove(board);

  QTCPP2048_CHECK_ASSERT(moved);
  QTCPP2048_CHECK_EQUAL(board, expected);
}

QTCPP2048_ADD_TEST(Calculation, up_move) {
  CalculationBlock block;
  std::vector<int32_t> board{2, 0, 0, 2, 2, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 2};
  std::vector<int32_t> expected{4, 0, 4, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  auto moved = block.CalculateUpMove(board);

  QTCPP2048_CHECK_ASSERT(moved);
  QTCPP2048_CHECK_EQUAL(board, expected);
}

QTCPP2048_ADD_TEST(Calculation, down_move) {
  CalculationBlock block;
  std::vector<int32_t> board{2, 0, 0, 2, 2, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 2};
  std::vector<int32_t> expected{0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 4, 0, 4, 4};

  auto moved = block.CalculateDownMove(board);

  QTCPP2048_CHECK_ASSERT(moved);
  QTCPP2048_CHECK_EQUAL(board, expected);
}

QTCPP2048_ADD_TEST(Calculation, no_valid_moves) {
  CalculationBlock block;
  std::vector<int32_t> board{static_cast<int32_t>(kTwo),
                             static_cast<int32_t>(kFour),
                             static_cast<int32_t>(kEight),
                             static_cast<int32_t>(kSixteen),
                             static_cast<int32_t>(kThirtyTwo),
                             static_cast<int32_t>(kSixtyFour),
                             static_cast<int32_t>(kOneTwentyEight),
                             static_cast<int32_t>(kTwoFiftySix),
                             static_cast<int32_t>(kFiveTwelve),
                             static_cast<int32_t>(kOneThousandTwentyFour),
                             static_cast<int32_t>(kTwo),
                             static_cast<int32_t>(kFour),
                             static_cast<int32_t>(kEight),
                             static_cast<int32_t>(kSixteen),
                             static_cast<int32_t>(kThirtyTwo),
                             static_cast<int32_t>(kSixtyFour)};

  QTCPP2048_CHECK_ASSERT(!block.CheckRowValid(board));
  QTCPP2048_CHECK_ASSERT(!block.CheckColumnValid(board));
}
