#ifndef CPP3_SMARTCALC_V2_1_DEPOSITCONTROLLER_H
#define CPP3_SMARTCALC_V2_1_DEPOSITCONTROLLER_H

#include "depositModel.h"

namespace s21 {
class depositControl {
 public:
  depositControl(double deposit_amount, double percent, int period,
                 double tax_rate, bool capitalization);

  void depositCalc();

  void printTable(int *date, double *add_percent, double *balance_change,
                  double *payment, double *temp_amount);

  int GetPeriod() { return d_.GetPeriod(); }
  double GetTaxAmount() { return d_.GetTaxAmount(); }
  double GetAccuredInterest() { return d_.GetAccuredInterest(); }
  double GetDepositAmount() { return d_.GetDepositAmount(); }
  bool GetTableEmpty() { return d_.GetTableEmpty(); }
  void pushDate(int d) { d_.pushDate(d); }
  void pushUp(double sum, int date, int up_down);
  void pushDown(double sum, int date, int up_down);

 private:
  deposit d_;
};

};  // namespace s21

#endif  // CPP3_SMARTCALC_V2_1_DEPOSITCONTROLLER_H