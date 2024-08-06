#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QDate>
#include <QDialog>
#include <QTableWidget>

#include "depositController.h"

namespace Ui {
class Depositwindow;
}

class Depositwindow : public QDialog {
  Q_OBJECT

 public:
  explicit Depositwindow(QWidget *parent = nullptr);
  ~Depositwindow();

 private slots:
  void on_Depos_pushButton_clicked();
  void on_comboBox_period_activated(int index, double *period);

 private:
  Ui::Depositwindow *ui;
  void depos_table_func(s21::depositControl *dp);
  int topUp_func(s21::depositControl *dp, QDate dateToday);
  int withdrawal_func(s21::depositControl *dp, QDate dateToday);
  int pay_date_func(s21::depositControl *dp, int payment_periodicity,
                    int *table_row);
  void year_payment(s21::depositControl *dp, int *table_row);
  void months_payment(s21::depositControl *dp, int *table_row, int n);
  void weekly_payment(s21::depositControl *dp, int *table_row);
};

#endif  // DEPOSITWINDOW_H
