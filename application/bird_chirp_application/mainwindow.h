#pragma once
#include <QMainWindow>

namespace Ui {
class BirdChirp;
}

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

 private:
  Ui::BirdChirp *ui;
};
