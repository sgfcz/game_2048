#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <QKeyEvent>
#include <vector>

#include "CalculationBlock.h"
#include "ui_MainWindow.h"

class MainWindow final : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = Q_NULLPTR);
  ~MainWindow() override;

  void start();

 protected:
  void keyPressEvent(QKeyEvent *event) override;  // 按键响应事件

 private:
  Ui::MainWindow ui_{};
  bool start_ = false;                                  // 是否开始
  std::vector<int> saveFreeBlock_;                      // 存储还能用于随机和生成的格子
  std::vector<int> saveBlockIndex_;                     // 存储格子里面的数字
  std::vector<std::vector<int>> saveHistoryIndex_;      // 存储所有的历史步
  std::shared_ptr<CalculationBlock> calculationBlock_;  // 计算格子的类

  void End(bool moved);           // 判断游戏是否结束
  void MoveLeft();                // 按下左移动
  void MoveRight();               // 按下右移动
  void MoveUp();                  // 按下上移动
  void MoveDown();                // 按下下移动
  void CreateBlock();             // 生成一个按钮
  void SetAllBlock();             // 设置已有格子
  void ClearAllBlock();           // 清空已经存在的所有格子
  void CalculateFreeBlockList();  // 重新计算用于随即的格子

 private slots:
  void slotClickedNewGame();   // 点击新游戏按钮响应槽函数
  void slotClickedPrevious();  // 点击返回上一步按钮响应槽函数
};

#endif  // MAINWINDOW_H_INCLUDED
