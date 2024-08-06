#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>
#include <QTableWidget>

#include "creditController.h"

namespace Ui {
class Creditwindow;
}

class Creditwindow : public QDialog {
  Q_OBJECT

 public:
  explicit Creditwindow(QWidget *parent = nullptr);
  ~Creditwindow();

 private slots:
  void on_result_Button_clicked();
  void table_func(s21::creditControl *cr, double *mount_p_max,
                  double *mount_p_min);

 private:
  Ui::Creditwindow *ui;
};

#endif  // CREDITWINDOW_H
