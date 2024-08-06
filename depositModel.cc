#include "depositModel.h"

namespace s21 {

deposit::deposit(double deposit_amount, double percent, int period,
                 double tax_rate, bool capitalization)
    : deposit_amount_(deposit_amount),
      percent_(percent),
      period_(period),
      tax_rate_(tax_rate),
      capitalization_(capitalization),
      accured_interest_(0) {}

deposit::contrib::contrib(double sum, int date, int up_down)
    : sum_(sum), date_(date), up_down_(up_down) {}

deposit::table::table(int date, double add_percent, double balance_change,
                      double payment, double temp_amount)
    : date_(date),
      add_percent_(add_percent),
      balance_change_(balance_change),
      payment_(payment),
      temp_amount_(temp_amount) {}

void deposit::depositCalc() {
  double temp_amount = deposit_amount_;
  double day_percent = percent_ / 36500;
  double balance_change = 0;
  double payment = 0;
  double sum_percent = 0;
  int payment_date = date_.front();
  date_.pop();
  for (int date = 1; date <= period_; date++) {
    double add_percent = day_percent * temp_amount;
    accured_interest_ += add_percent;
    upTop(&balance_change, date);
    downTop(&balance_change, &payment, date, temp_amount);
    if ((temp_amount + balance_change < 0)) temp_amount += balance_change;
    if (capitalization_) {
      balance_change += add_percent;
    } else {
      payment += add_percent;
    }
    sum_percent += add_percent;
    if (payment_date == date) {
      temp_amount += balance_change;
      table t(date, sum_percent, balance_change, payment, temp_amount);
      table_.push(t);
      balance_change = 0;
      payment = 0;
      sum_percent = 0;
      if (!date_.empty()) {
        payment_date = date_.front();
        date_.pop();
      }
    }
  }
  tax_amount_ = accured_interest_ * tax_rate_ / 100;
  deposit_amount_ = temp_amount;
}

void deposit::printTable(int *date, double *add_percent, double *balance_change,
                         double *payment, double *temp_amount) {
  *date = table_.front().GetDate();
  *add_percent = table_.front().GetAddPercent();
  *balance_change = table_.front().GetBalanceChange();
  *payment = table_.front().GetPayment();
  *temp_amount = table_.front().GetTempAmount();
  table_.pop();
}

void deposit::upTop(double *balance_change, int date) {
  if (!up_.empty()) {
    if (up_.front().GetDate() == date) {
      *balance_change += up_.front().GetSum();
      up_.pop();
    }
  }
}

void deposit::downTop(double *balance_change, double *payment, int date,
                      double temp_amount) {
  if (!down_.empty()) {
    if (down_.front().GetDate() == date) {
      double temp_sum = down_.front().GetSum();
      if (temp_amount - temp_sum >= 0) {
        *balance_change -= temp_sum;
        *payment += temp_sum;
      }
      down_.pop();
    }
  }
}

void deposit::pushUp(double sum, int date, int up_down) {
  contrib c(sum, date, up_down);
  up_.push(c);
}

void deposit::pushDown(double sum, int date, int up_down) {
  contrib d(sum, date, up_down);
  down_.push(d);
}

}  // namespace s21