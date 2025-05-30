#ifndef SHOW_BLOCK_H
#define SHOW_BLOCK_H

#include <QLabel>
#include <utility>
#include <vector>

#include "Framework.h"

class BlockColor {
public:
  BlockColor(const int number, std::string color) : number_(number), color_(std::move(color)) {}

  int GetNumber() { return number_; }
  std::string GetColor() { return color_; }

private:
  int number_;
  std::string color_;
};

class Block final : public QLabel {
  Q_OBJECT

 public:
  explicit Block(int number, QWidget *parent = Q_NULLPTR);
  ~Block() override;

  void SetBlock(int number);

 private:
  void BlockSetColor(int moveNumber);
  void BlockSetFont(int number);
  auto BlockGetColor(int number) -> std::string;

  int blockNumber_ = -1;
  int blockColor_ = -1;

  std::vector<BlockColor> colorMap_ {{BlockColor(kTwo, "#EEE4DA")},
                                  {BlockColor(kFour, "#EDE0C8")},
                                  {BlockColor(kEight, "#F2B179")},
                                  {BlockColor(kSixteen, "#F59563")},
                                  {BlockColor(kThirtyTwo, "#F67C5F")},
                                  {BlockColor(kSixtyFour, "#F65E3B")},
                                  {BlockColor(kOneTwentyEight, "#EDCF72")},
                                  {BlockColor(kTwoFiftySix, "#EDCC61")},
                                  {BlockColor(kFiveTwelve, "#EDC850")},
                                  {BlockColor(kOneThousandTwentyFour, "#EDC53F")},
                                  {BlockColor(kTwoThousandFortyEight, "#EDC22E")}};
};

#endif
