//
// Created by shaw on 25-3-29.
//
#include "CalculationBlock.h"

#include <algorithm>
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
  for (int col = 0; col < kGameColumn; col++) {
    for (int row = 0; row < kGameRow; row++) {
      int index = row * kGameColumn + col;
      if (block_index[index] == 0) {
        return true;
      }

      if (row < kGameRow - 1 && block_index[index] == block_index[index + kGameColumn]) {
        return true;
      }
    }
  }

  return column_move_able;
}

bool CalculationBlock::CalculateLeftMove(std::vector<int32_t> &block_index) {
  bool move_action = false;

  for (int i = 0; i < kGameRow; i++) {
    int index = i * kGameRow;
    std::vector<int32_t> current{block_index[index], block_index[index + 1], block_index[index + 2],
                                 block_index[index + 3]};
    auto list = ListCalculate(current);

    if (list != current) {
      move_action = true;
      std::copy(list.begin(), list.end(), block_index.begin() + index);
    }
  }

  return move_action;
}

bool CalculationBlock::CalculateRightMove(std::vector<int32_t> &block_index) {
  bool move_action = false;
  for (int i = 0; i < kGameRow; i++) {
    int index = i * kGameRow;
    std::vector<int32_t> current{block_index[index], block_index[index + 1], block_index[index + 2],
                                 block_index[index + 3]};
    std::reverse(current.begin(), current.end());
    auto list = ListCalculate(current);
    std::reverse(list.begin(), list.end());

    if (list != std::vector<int32_t>{block_index[index], block_index[index + 1], block_index[index + 2],
                                     block_index[index + 3]}) {
      move_action = true;
      std::copy(list.begin(), list.end(), block_index.begin() + index);
    }
  }

  return move_action;
}

bool CalculationBlock::CalculateUpMove(std::vector<int32_t> &block_index) {
  bool move_action = false;

  for (int col = 0; col < kGameColumn; col++) {
    std::vector<int32_t> current;
    current.reserve(kGameRow);
    for (int row = 0; row < kGameRow; row++) {
      current.push_back(block_index[row * kGameColumn + col]);
    }

    auto list = ListCalculate(current);
    if (list != current) {
      move_action = true;
      for (int row = 0; row < kGameRow; row++) {
        block_index[row * kGameColumn + col] = list[row];
      }
    }
  }

  return move_action;
}

bool CalculationBlock::CalculateDownMove(std::vector<int32_t> &block_index) {
  bool move_action = false;

  for (int col = 0; col < kGameColumn; col++) {
    std::vector<int32_t> current;
    current.reserve(kGameRow);
    for (int row = 0; row < kGameRow; row++) {
      current.push_back(block_index[row * kGameColumn + col]);
    }

    auto original = current;
    std::reverse(current.begin(), current.end());
    auto list = ListCalculate(current);
    std::reverse(list.begin(), list.end());

    if (list != original) {
      move_action = true;
      for (int row = 0; row < kGameRow; row++) {
        block_index[row * kGameColumn + col] = list[row];
      }
    }
  }

  return move_action;
}

bool CalculationBlock::CheckRowValid(const std::vector<int32_t> &block_index) {
  bool row_move_able = false;

  // 横向查看是否游戏结束
  for (int row = 0; row < kGameRow; row++) {
    for (int col = 0; col < kGameColumn; col++) {
      int index = row * kGameColumn + col;
      if (block_index[index] == 0) {
        return true;
      }

      if (col < kGameColumn - 1 && block_index[index] == block_index[index + 1]) {
        return true;
      }
    }
  }

  return row_move_able;
}

auto CalculationBlock::ListCalculate(const std::vector<int32_t> &numList) -> std::vector<int32_t> {
  std::vector<int32_t> filtered;
  filtered.reserve(kGameRow);
  for (const auto num : numList) {
    if (num != 0) {
      filtered.push_back(num);
    }
  }

  std::vector<int32_t> merged;
  merged.reserve(kGameRow);
  for (size_t i = 0; i < filtered.size(); i++) {
    if (i + 1 < filtered.size() && filtered[i] == filtered[i + 1]) {
      merged.push_back(filtered[i] * 2);
      i++;
    } else {
      merged.push_back(filtered[i]);
    }
  }

  merged.resize(kGameRow, 0);
  return merged;
}
