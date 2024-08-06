#include "mainwindow.h"

#include <QDialog>
#include <QLabel>

#include "creditwindow.h"
#include "depositwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_open, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_close, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButton_graf, SIGNAL(clicked()), this, SLOT(plot_func()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();

  QString str_label = ui->result_show->text();
  if (str_label == "0") {
    if (button->text() == ".") {
      str_label += button->text();
    } else {
      str_label = button->text();
    }
  } else {
    str_label += button->text();
  }
  ui->result_show->setText(str_label);
}

void MainWindow::on_pushButton_AC_clicked() {
  QString str1_label = "0";
  ui->result_show->setText(str1_label);
}

void MainWindow::on_pushButton_ravno_clicked() {
  double result = 0;
  double x = ui->x_value_line->text().toDouble();
  QString str_label = (ui->result_show->text());
  QByteArray ba = str_label.toLocal8Bit();
  char *str_base = ba.data();
  int error = 0;
  s21::calcControl calc(str_base, x);
  if (strlen(str_base) > 255) {
    error = 1;
  } else {
    error = calc.verification();
    if (!error) {
      try {
        result = calc.calculate();
      } catch (...) {
        error = 1;
      }
    }
  }
  if (error) {
    ui->result_show->setText("ERROR");
  } else {
    char result_str[1000] = {0};
    if (result == (long long int)result)
      sprintf(result_str, "%lld", (long long int)result);
    else
      sprintf(result_str, "%.7lf", result);
    ui->result_show->setText(result_str);
  }
}

void MainWindow::plot_func() {
  QString str_label = (ui->result_show->text());
  QByteArray ba = str_label.toLocal8Bit();
  char *str_verif = ba.data();
  s21::calcControl calc(str_verif, 0);
  int error = calc.verification();
  if (error) {
    ui->result_show->setText("ERROR");
  } else {
    if (flag_plot) {
      ui->widget->graph(0)->data()->clear();
      ui->widget->replot();
    }
    QVector<double> x, y;
    double X = 0;
    int x_max = ui->x_max_line->text().toInt();
    if (x_max > 1000000) x_max = 1000000;
    int x_min = ui->x_min_line->text().toInt();
    if (x_min > 1000000) x_min = 1000000;
    int y_max = ui->y_max_line->text().toInt();
    if (y_max > 1000000) y_max = 1000000;
    int y_min = ui->y_min_line->text().toInt();
    if (y_min > 1000000) y_min = 1000000;
    double xBegin = x_min;
    double xEnd = x_max;
    double h = (double)(x_max - x_min) / 10000;

    ui->widget->xAxis->setRange(x_min, x_max);
    ui->widget->yAxis->setRange(y_min, y_max);

    for (X = xBegin; X <= xEnd && !error; X += h) {
      s21::calcControl graf(str_verif, X);
      x.push_back(X);
      y.push_back(graf.calculate());
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    flag_plot = 1;
  }
}

void MainWindow::on_pushButton_depos_clicked() {
  Depositwindow depositwindow;
  depositwindow.setModal(true);
  depositwindow.exec();
}

void MainWindow::on_pushButton_cred_clicked() {
  Creditwindow creditwindow;
  creditwindow.setModal(true);
  creditwindow.exec();
}

void MainWindow::on_pushButton_del_clicked() {
  QString str_label = (ui->result_show->text());
  str_label.chop(1);
  ui->result_show->setText(str_label);
}
