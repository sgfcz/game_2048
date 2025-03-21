﻿#pragma once
#include <QLabel>
#include <utility>
#include <vector>

class BlockColor {
 public:
  BlockColor(const int number, std::string color) : number(number), color(std::move(color)) {}
  int GetNumber() { return number; }
  auto GetColor() -> std::string { return color; }

 private:
  int number;
  std::string color;
};

class Block : public QLabel {
  Q_OBJECT
 public:
  explicit Block(int number, QWidget *parent = Q_NULLPTR);
  ~Block() override;

  void SetBlock(int number);

 private:
  std::vector<BlockColor> _colorMap{
      {BlockColor(2, "#eee4da")},    {BlockColor(4, "#ede0c8")},   {BlockColor(8, "#f2b179")},
      {BlockColor(16, "#f59563")},   {BlockColor(32, "#f67c5f")},  {BlockColor(64, "#f65e3b")},
      {BlockColor(128, "#edcf72")},  {BlockColor(256, "#edcc61")}, {BlockColor(512, "#edc850")},
      {BlockColor(1024, "#edc53f")}, {BlockColor(2048, "#edc22e")}};

  int _blockNumber = -1;
  int _blockColor = -1;

 private:
  void BlockSetColor(int moveNumber);
  void BlockSetFont(int number);
  std::string BlockGetColor(int number);
};
