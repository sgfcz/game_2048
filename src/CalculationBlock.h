//
// Created by shaw on 25-3-29.
//

#ifndef CALCULATIONBLOCK_H
#define CALCULATIONBLOCK_H
#include <cstdint>
#include <vector>

#include "Framework.h"

class CalculationBlock {
 public:
  CalculationBlock();
  ~CalculationBlock() = default;

  uint32_t RandomGenerateBlock(size_t size);
  int32_t RandomGenerateNumber();

  bool CheckRowValid(const std::vector<int32_t> &);     // 检查行的合法性
  bool CheckColumnValid(const std::vector<int32_t> &);  // 检查列的合法性

  bool CalculateLeftMove(std::vector<int32_t> &);          // 计算左移
  bool CalculateRightMove(std::vector<int32_t> &);         // 计算右移
  bool CalculateUpMove(std::vector<int32_t> &);            // 计算上移
  bool CalculateDownMove(std::vector<int32_t> &);          // 计算下移
  std::vector<int> ListCalculate(std::vector<int32_t> numList);  // 使用递归计算
};

#endif  // CALCULATIONBLOCK_H
