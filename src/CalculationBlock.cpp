//
// Created by shaw on 25-3-29.
//
#include "CalculationBlock.h"

#include <random>

CalculationBlock::CalculationBlock() = default;

auto CalculationBlock::RandomGenerateBlock() -> int {
  // 设置随机格子
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(0, saveFreeBlock_.size() - 1);

  int block_widget_index = saveFreeBlock_[dist6(rng)];
  return block_widget_index;
}

auto CalculationBlock::RandomGenerateNumber() -> int {
  std::mt19937 engine(std::random_device{}());
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  double random_number = distribution(engine);
  int set_number = random_number < 0.9 ? 2 : 4;
  return set_number;
}