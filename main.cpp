#include "include/MainWindow.h"

auto main(int argc, char *argv[]) -> int {
  QApplication app(argc, argv);
  MainWindow main_window;
  main_window.show();

  return QApplication::exec();
}
