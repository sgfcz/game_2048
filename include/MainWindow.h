#pragma once
#include <QKeyEvent>
#include <QtCore/qtmetamacros.h>
#include <QtWidgets/QMainWindow>
#include <QtWidgets>

#include <map>
#include <vector>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = Q_NULLPTR);
  ~MainWindow() override;

  void start();

private:
  Ui::MainWindow ui{};
  bool _start = false;             // 是否开始
  std::vector<int> _saveFreeBlock; // 存储还能用于随机和生成的格子
  std::vector<int> _saveBlockIndex; // 存储格子里面的数字
  std::vector<std::vector<int>> _saveHistoryIndex; // 存储所有的历史步

private:
  void end();                                    // 判断游戏是否结束
  void moveLeft();                               // 按下左移动
  void moveRight();                              // 按下右移动
  void moveUp();                                 // 按下上移动
  void movedown();                               // 按下下移动
  void createblock();                            // 生成一个按钮
  void keyPressEvent(QKeyEvent *event) override; // 按键响应事件

private slots:
  void slotClickedNewGame();  // 点击新游戏按钮响应槽函数
  void slotClickedPrevious(); // 点击返回上一步按钮响应槽函数
};