#include "depositController.h"

namespace s21 {

depositControl::depositControl(double deposit_amount, double percent,
                               int period, double tax_rate, bool capitalization)
    : d_(deposit_amount, percent, period, tax_rate, capitalization){};

void depositControl::depositCalc() { d_.depositCalc(); }

void depositControl::printTable(int *date, double *add_percent,
                                double *balance_change, double *payment,
                                double *temp_amount) {
  d_.printTable(date, add_percent, balance_change, payment, temp_amount);
}

void depositControl::pushUp(double sum, int date, int up_down) {
  d_.pushUp(sum, date, up_down);
}

void depositControl::pushDown(double sum, int date, int up_down) {
  d_.pushDown(sum, date, up_down);
}

};  // namespace s21