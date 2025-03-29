#pragma once
#include <QLabel>
#include <utility>
#include <vector>

constexpr uint64_t kTwo = 2;
constexpr uint64_t kFour = 4;
constexpr uint64_t kEight = 8;
constexpr uint64_t kSixteen = 16;
constexpr uint64_t kThirtyTwo = 32;
constexpr uint64_t kSixtyFour = 64;
constexpr uint64_t kOneTwentyEight = 128;
constexpr uint64_t kTwoFiftySix = 256;
constexpr uint64_t kFiveTwelve = 512;
constexpr uint64_t kOneThousandTwentyFour = 1024;
constexpr uint64_t kTwoThousandFortyEight = 2048;

class BlockColor {
 public:
  BlockColor(const int number, std::string color) : number_(number), color_(std::move(color)) {}

  [[nodiscard]] auto GetNumber() const -> int { return number_; }
  auto GetColor() -> std::string { return color_; }

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

  std::vector<BlockColor> colorMap_{{BlockColor(kTwo, "#EEE4DA")},
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

  int blockNumber_ = -1;
  int blockColor_ = -1;
};
