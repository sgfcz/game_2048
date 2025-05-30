//
// Created by shaw on 25-3-29.
//

#ifndef CALCULATIONBLOCK_H
#define CALCULATIONBLOCK_H

class CalculationBlock {
public:
  CalculationBlock();
  ~CalculationBlock() = default;

  auto RandomGenerateBlock() -> int;
  auto RandomGenerateNumber() -> int;
};

#endif //CALCULATIONBLOCK_H
