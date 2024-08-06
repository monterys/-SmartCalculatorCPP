#ifndef CPP3_SMARTCALC_V2_1_DEPOSITMODEL_H
#define CPP3_SMARTCALC_V2_1_DEPOSITMODEL_H

#include <cmath>
#include <queue>

namespace s21 {
class deposit {
 public:
  class table {
   public:
    table(int date, double add_percent, double balance_change, double payment,
          double temp_amount);

    double GetDate() { return date_; }
    double GetAddPercent() { return add_percent_; }
    double GetBalanceChange() { return balance_change_; }
    double GetPayment() { return payment_; }
    double GetTempAmount() { return temp_amount_; }

   private:
    int date_;
    double add_percent_;
    double balance_change_;
    double payment_;
    double temp_amount_;
  };

  class contrib {
   public:
    contrib(double sum, int date, int up_down);

    double GetSum() { return sum_; }
    int GetDate() { return date_; }
    double GetUpDown() { return up_down_; }

   private:
    double sum_;
    int date_;
    int up_down_;
  };

  deposit(double deposit_amount, double percent, int period, double tax_rate,
          bool capitalization);

  void depositCalc();
  void printTable(int *date, double *add_percent, double *balance_change,
                  double *payment, double *temp_amount);

  int GetPeriod() { return period_; }
  double GetTaxAmount() { return tax_amount_; }
  double GetAccuredInterest() { return accured_interest_; }
  double GetDepositAmount() { return deposit_amount_; }
  bool GetTableEmpty() { return table_.empty(); }
  void pushDate(int d) { date_.push(d); }
  void pushUp(double sum, int date, int up_down);
  void pushDown(double sum, int date, int up_down);

 private:
  void upTop(double *balance_change, int date);
  void downTop(double *balance_change, double *payment, int date,
               double temp_amount);

  std::queue<table> table_;
  std::queue<contrib> up_;
  std::queue<contrib> down_;
  std::queue<int> date_;
  double deposit_amount_;
  double percent_;
  int period_;
  double tax_rate_;
  bool capitalization_;
  double accured_interest_;
  double tax_amount_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_1_DEPOSITMODEL_H