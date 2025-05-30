//
// Created by shaw on 25-3-29.
//
#include "CalculationBlock.h"

#include <random>

CalculationBlock::CalculationBlock() = default;

uint32_t CalculationBlock::RandomGenerateBlock(const size_t size) {
  // 设置随机格子
  std::mt19937 engine(std::random_device{}());
  std::uniform_int_distribution<std::mt19937::result_type> distribution(0, size - 1);

  uint32_t block_widget_index = distribution(engine);
  return block_widget_index;
}

int32_t CalculationBlock::RandomGenerateNumber() {
  std::mt19937 engine(std::random_device{}());
  std::uniform_real_distribution distribution(0.0, 1.0);

  double random_number = distribution(engine);
  int set_number = random_number < 0.9 ? 2 : 4;
  return set_number;
}

bool CalculationBlock::CheckColumnValid(const std::vector<int32_t> &block_index) {
  bool column_move_able = false;

  // 纵向查看是否还有活动空间
  for (int i = 0; i < block_index.size() - 4; i++) {
    if (block_index[i] == block_index[i + 4] || block_index[i + 4] == 0) {
      column_move_able = true;
      break;
    }
  }

  return column_move_able;
}

bool CalculationBlock::CalculateLeftMove(std::vector<int32_t> &block_index) {
  bool move_action = false;

  for (int i = 0; i < kGameRow; i++) {
    int index = i * kGameRow;
    auto list = ListCalculate(std::vector<int>{block_index[index], block_index[index + 1],
                                               block_index[index + 2], block_index[index + 3]});

    if (list.empty()) {
      continue;
    }

    list.resize(4);
    move_action = true;
    std::copy(list.begin(), list.end(), block_index.begin() + index);
  }

  return move_action;
}

bool CalculationBlock::CalculateRightMove(std::vector<int32_t> &block_index) {
  bool move_action = false;
  for (int i = 0; i < kGameRow; i++) {
    int index = i * kGameRow;
    auto list = ListCalculate(std::vector<int>{block_index[index], block_index[index + 1],
                                               block_index[index + 2], block_index[index + 3]});

    if (list.empty()) {
      continue;
    }

    list.resize(4);
    move_action = true;
    std::copy(list.begin(), list.end(), block_index.begin() + index);
  }

  return move_action;
}

bool CalculationBlock::CalculateUpMove(std::vector<int32_t> &block_index) {
  bool move_action = false;

  return move_action;
}

bool CalculationBlock::CalculateDownMove(std::vector<int32_t> &block_index) {
  bool move_action = false;

  return move_action;
}

bool CalculationBlock::CheckRowValid(const std::vector<int32_t> &block_index) {
  bool row_move_able = false;

  // 横向查看是否游戏结束
  for (int i = 0; i < block_index.size() - 1; i++) {
    if (block_index[i] == block_index[i + 1] || block_index[i + 1] == 0) {
      row_move_able = true;
      break;
    }
  }

  return row_move_able;
}

auto CalculationBlock::ListCalculate(std::vector<int> numList) -> std::vector<int> {
  for (int i = 0; i < numList.size() - 1; i++) {
    if (numList[i] == numList[i + 1] && numList[i] != 0) {
      numList[i] = numList[i] * 2;
      numList[i + 1] = 0;
    }
  }

  for (auto i = numList.begin(); i != numList.end();) {
    if (*i == 0) {
      i = numList.erase(i);
      continue;
    }

    ++i;
  }

  return numList;
}