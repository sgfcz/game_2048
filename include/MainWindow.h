#pragma once
#include <QtCore/qtmetamacros.h>
#include <QtWidgets>
#include <QtWidgets/QMainWindow>
#include <QKeyEvent>

#include <map>
#include <vector>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
  public:
    explicit MainWindow(QWidget* parent = Q_NULLPTR);
    ~MainWindow() override;

    void start();
  private:
    Ui::MainWindow ui{};
    bool _start = false;
    std::vector<int> _saveBlockIndex;

  private:
    void end();
    void moveLeft();
    void moveRight();
    void moveUp();
    void movedown();

    void makeblock();

    void keyPressEvent(QKeyEvent* event) override;

  private slots:
    void slotClickedNewGame();
    void slotClickedPrevious();

};