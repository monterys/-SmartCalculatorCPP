#include "creditController.h"

namespace s21 {
creditControl::creditControl(double amount, double percent, double period)
    : cr_(amount, percent, period) {}

void creditControl::differential() { cr_.differentialCreditCalc(); }

void creditControl::annuitant() { cr_.annuitantCreditCalc(); }

void creditControl::print(double *overpayment, double *monthly_payment,
                          double *temp_amount, int *month) {
  cr_.dmp(overpayment, monthly_payment, temp_amount, month);
}

double creditControl::GetOverpayment() { return cr_.GetOverpayment(); }

double creditControl::GetMonthlyPayment() { return cr_.GetMonthlyPayment(); }

double creditControl::GetTotalPayment() { return cr_.GetTotalPayment(); }

bool creditControl::tableEmpty() { return cr_.tableEmpty(); }

}  // namespace s21