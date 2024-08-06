#include "depositwindow.h"

#include "ui_depositwindow.h"

Depositwindow::Depositwindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::Depositwindow) {
  ui->setupUi(this);
}

Depositwindow::~Depositwindow() { delete ui; }

void Depositwindow::on_Depos_pushButton_clicked() {
  QDate dateToday = QDate::currentDate();
  ui->tableWidget->clear();
  double deposit_amount = ui->line_deposit_amount->text().toDouble();
  double percent = ui->line_percent->text().toDouble();
  double period = ui->line_period->text().toDouble();
  double tax_rate = ui->line_tax_rate->text().toDouble();
  int capitalization = 0;
  int payment_periodicity = ui->payment_periodicity->currentIndex();
  ;  // 0-день, 1-неделя, 2-месяц, 3-квартал, 4-год, 5-в конце
  double accured_interest = 0;
  double tax_amount = 0;
  char temp_str[1000] = {0};
  if (ui->capitalization->isChecked()) capitalization = 1;
  int index = ui->comboBox_period->currentIndex();
  int table_row = 0;
  on_comboBox_period_activated(index, &period);
  if (period > 18263) {
    period = 18263;
    ui->line_period->setText("50");
    ui->comboBox_period->setCurrentIndex(2);
  }
  s21::depositControl dp(deposit_amount, percent, period, tax_rate,
                         capitalization);
  pay_date_func(&dp, payment_periodicity, &table_row);
  QStringList headers;
  headers << "дата"
          << "начисленные %"
          << "изменение баланса"
          << "выплата"
          << "остаток";
  ui->tableWidget->setRowCount(table_row);
  ui->tableWidget->setColumnCount(5);
  ui->tableWidget->setHorizontalHeaderLabels(headers);
  topUp_func(&dp, dateToday);
  withdrawal_func(&dp, dateToday);
  dp.depositCalc();
  accured_interest = dp.GetAccuredInterest();
  sprintf(temp_str, "%.2lf", accured_interest);
  ui->accured_interest->setText(temp_str);
  deposit_amount = dp.GetDepositAmount();
  sprintf(temp_str, "%.2lf", deposit_amount);
  ui->deposit_amount_end->setText(temp_str);
  tax_amount = dp.GetTaxAmount();
  sprintf(temp_str, "%.2lf", tax_amount);
  ui->tax_amount->setText(temp_str);
  depos_table_func(&dp);
}

int Depositwindow::pay_date_func(s21::depositControl *dp,
                                 int payment_periodicity, int *table_row) {
  if (payment_periodicity == 0) {
    int date = 0;
    while (date <= (*dp).GetPeriod()) {
      date++;
      (*dp).pushDate(date);
      *table_row = *table_row + 1;
    }
  } else if (payment_periodicity == 1) {
    weekly_payment(dp, table_row);
  } else if (payment_periodicity == 2) {
    months_payment(dp, table_row, 1);
  } else if (payment_periodicity == 3) {
    months_payment(dp, table_row, 3);
  } else if (payment_periodicity == 4) {
    year_payment(dp, table_row);
  } else if (payment_periodicity == 5) {
    (*dp).pushDate((*dp).GetPeriod());
    *table_row = *table_row + 1;
  }
  return 0;
}

void Depositwindow::weekly_payment(s21::depositControl *dp, int *table_row) {
  int date = 7;
  while (date <= (*dp).GetPeriod()) {
    (*dp).pushDate(date);
    date = date + 7;
    *table_row = *table_row + 1;
  }
  int lost = (*dp).GetPeriod() % 7;
  if (lost) {
    (*dp).pushDate(date);
    *table_row = *table_row + 1;
  }
}

void Depositwindow::months_payment(s21::depositControl *dp, int *table_row,
                                   int n) {
  int date = 0;
  QDate dateToday = QDate::currentDate();
  QDate topDate = dateToday.addMonths(n);
  int lost = (*dp).GetPeriod();
  date = date + dateToday.daysTo(topDate);
  while (date <= (*dp).GetPeriod()) {
    (*dp).pushDate(date);
    QDate tempDate = topDate.addMonths(n);
    date = date + topDate.daysTo(tempDate);
    lost = lost - topDate.daysTo(tempDate);
    topDate = tempDate;
    *table_row = *table_row + 1;
  }
  if (lost) {
    (*dp).pushDate(date);
    *table_row = *table_row + 1;
  }
}

void Depositwindow::year_payment(s21::depositControl *dp, int *table_row) {
  int date = 0;
  QDate dateToday = QDate::currentDate();
  QDate topDate = dateToday.addYears(1);
  int lost = (*dp).GetPeriod();
  date = date + dateToday.daysTo(topDate);
  while (date <= (*dp).GetPeriod()) {
    (*dp).pushDate(date);
    QDate tempDate = topDate.addYears(1);
    date = date + topDate.daysTo(tempDate);
    lost = lost - topDate.daysTo(tempDate);
    topDate = tempDate;
    *table_row = *table_row + 1;
  }
  if (lost) {
    (*dp).pushDate(date);
    *table_row = *table_row + 1;
  }
}

int Depositwindow::withdrawal_func(s21::depositControl *dp, QDate dateToday) {
  QDate topControl;
  if (ui->down_checkBox_1->isChecked()) {
    QDate topDate = ui->down_dateEdit_1->date();
    if (topDate > dateToday) {
      topControl = topDate;
      double topUp = ui->down_1->text().toDouble();
      int d = dateToday.daysTo(topDate);
      (*dp).pushDown(topUp, d, 0);
    }
  }
  if (ui->down_checkBox_2->isChecked()) {
    QDate topDate = ui->down_dateEdit_2->date();
    if (topDate > topControl) {
      topControl = topDate;
      double topUp = ui->down_2->text().toDouble();
      int d = dateToday.daysTo(topDate);
      (*dp).pushDown(topUp, d, 0);
    }
  }
  if (ui->down_checkBox_3->isChecked()) {
    QDate topDate = ui->down_dateEdit_3->date();
    if (topDate > topControl) {
      topControl = topDate;
      double topUp = ui->down_3->text().toDouble();
      int d = dateToday.daysTo(topDate);
      (*dp).pushDown(topUp, d, 0);
    }
  }
  if (ui->down_checkBox_4->isChecked()) {
    QDate topDate = ui->down_dateEdit_4->date();
    if (topDate > topControl) {
      topControl = topDate;
      double topUp = ui->down_4->text().toDouble();
      int d = dateToday.daysTo(topDate);
      (*dp).pushDown(topUp, d, 0);
    }
  }
  if (ui->down_checkBox_5->isChecked()) {
    QDate topDate = ui->down_dateEdit_5->date();
    if (topDate > topControl) {
      topControl = topDate;
      double topUp = ui->down_5->text().toDouble();
      int d = dateToday.daysTo(topDate);
      (*dp).pushDown(topUp, d, 0);
    }
  }
  return 0;
}

int Depositwindow::topUp_func(s21::depositControl *dp, QDate dateToday) {
  QDate topControl;
  if (ui->top_checkBox_1->isChecked()) {
    QDate topDate = ui->top_dateEdit_1->date();
    if (topDate > dateToday) {
      topControl = topDate;
      double topUp = ui->top_1->text().toDouble();
      int d = dateToday.daysTo(topDate);
      (*dp).pushUp(topUp, d, 0);
    }
  }
  if (ui->top_checkBox_2->isChecked()) {
    QDate topDate = ui->top_dateEdit_2->date();
    if (topDate > topControl) {
      topControl = topDate;
      double topUp = ui->top_2->text().toDouble();
      int d = dateToday.daysTo(topDate);
      (*dp).pushUp(topUp, d, 0);
    }
  }
  if (ui->top_checkBox_3->isChecked()) {
    QDate topDate = ui->top_dateEdit_3->date();
    if (topDate > topControl) {
      topControl = topDate;
      double topUp = ui->top_3->text().toDouble();
      int d = dateToday.daysTo(topDate);
      (*dp).pushUp(topUp, d, 0);
    }
  }
  if (ui->top_checkBox_4->isChecked()) {
    QDate topDate = ui->top_dateEdit_4->date();
    if (topDate > topControl) {
      topControl = topDate;
      double topUp = ui->top_4->text().toDouble();
      int d = dateToday.daysTo(topDate);
      (*dp).pushUp(topUp, d, 0);
    }
  }
  if (ui->top_checkBox_5->isChecked()) {
    QDate topDate = ui->top_dateEdit_5->date();
    if (topDate > topControl) {
      topControl = topDate;
      double topUp = ui->top_5->text().toDouble();
      int d = dateToday.daysTo(topDate);
      (*dp).pushUp(topUp, d, 0);
    }
  }
  return 0;
}

void Depositwindow::depos_table_func(s21::depositControl *dp) {
  double temp_amount = 0, add_percent = 0, balance_change = 0, payment = 0;
  int date = 0;
  int rows = 0;
  QDate dateToday = QDate::currentDate();
  char temp_str[1000] = {0};
  while (!(*dp).GetTableEmpty()) {
    (*dp).printTable(&date, &add_percent, &balance_change, &payment,
                     &temp_amount);
    QDate date_table = dateToday.addDays(date);
    QString str_date = date_table.toString("dd/MM/yyyy");
    QTableWidgetItem *item1 = new QTableWidgetItem(str_date);
    ui->tableWidget->setItem(rows, 0, item1);
    sprintf(temp_str, "%.2lf", (add_percent));
    QTableWidgetItem *item2 = new QTableWidgetItem(QString(temp_str));
    ui->tableWidget->setItem(rows, 1, item2);
    sprintf(temp_str, "%.2lf", balance_change);
    QTableWidgetItem *item3 = new QTableWidgetItem(QString(temp_str));
    ui->tableWidget->setItem(rows, 2, item3);
    sprintf(temp_str, "%.2lf", payment);
    QTableWidgetItem *item4 = new QTableWidgetItem(QString(temp_str));
    ui->tableWidget->setItem(rows, 3, item4);
    sprintf(temp_str, "%.2lf", temp_amount);
    QTableWidgetItem *item5 = new QTableWidgetItem(QString(temp_str));
    ui->tableWidget->setItem(rows, 4, item5);
    rows++;
  }
}

void Depositwindow::on_comboBox_period_activated(int index, double *period) {
  QDate dateToday = QDate::currentDate();
  if (index == 0) {
    QDate tempDate = dateToday.addDays(*period);
    *period = dateToday.daysTo(tempDate);
  } else if (index == 1) {
    QDate tempDate = dateToday.addMonths(*period);
    *period = dateToday.daysTo(tempDate);
  } else if (index == 2) {
    QDate tempDate = dateToday.addYears(*period);
    *period = dateToday.daysTo(tempDate);
  }
}
