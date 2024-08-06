#ifndef CPP3_SMARTCALC_V2_1_CREDITCONTROLLER_H
#define CPP3_SMARTCALC_V2_1_CREDITCONTROLLER_H

#include "creditModel.h"

namespace s21 {
class creditControl {
 public:
  creditControl(double amount, double percent, double period);

  void differential();
  void annuitant();
  void print(double *overpayment, double *monthly_payment, double *temp_amount,
             int *month);
  double GetOverpayment();
  double GetMonthlyPayment();
  double GetTotalPayment();
  bool tableEmpty();

 private:
  credit cr_;
};

};  // namespace s21

#endif  // CPP3_SMARTCALC_V2_1_CREDITCONTROLLER_H