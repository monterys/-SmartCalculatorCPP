#include <iostream>

#include "calcController.h"
#include "creditController.h"
#include "depositController.h"
#include "gtest/gtest.h"

TEST(calc, calc_1) {
  char str[256] = "2051+311.22";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = 2051 + 311.22;
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

TEST(calc, calc_2) {
  char str[256] = "1.32-1.8+0.036";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = 1.32 - 1.8 + 0.036;
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

TEST(calc, calc_3) {
  char str[256] = "1/((1/3)+1)";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = 0.75;
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

TEST(calc, calc_4) {
  char str[256] = "1/sin(3)";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = 1 / sin(3);
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

TEST(calc, calc_5) {
  char str[256] = "2^3";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = pow(2, 3);
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

TEST(calc, calc_6) {
  char str[256] = "1.4-asin(1)";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = 1.4 - asin(1);
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

TEST(calc, calc_7) {
  char str[256] = "(tan(2)/(2.5+3))";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = (tan(2) / (2.5 + 3));
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

TEST(calc, calc_8) {
  char str[256] = "1.4*cos(1/4)";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = 1.35648;
  ASSERT_EQ(status, 0);
  ASSERT_EQ(round(result * 100000) / 100000, correct);
}

TEST(calc, calc_9) {
  char str[256] = "-sin(0.732)*2";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = -1.33672;
  ASSERT_EQ(status, 0);
  ASSERT_EQ(round(result * 100000) / 100000, correct);
}

TEST(calc, calc_10) {
  char str[256] = "acos(1)";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = acos(1);
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

TEST(calc, calc_11) {
  char str[256] = "atan(-0.98)";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = atan(-0.98);
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

TEST(calc, calc_12) {
  char str[256] = "sqrt(27)";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = sqrt(27);
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

// TEST(calc, calc_13) {
//   char str[256] = "sqrt(-2)";
//   double x = 0;
//   s21::calcControl c(str, x);
//   int status = c.verification();
//   ASSERT_EQ(status, 1);
// }

TEST(calc, calc_14) {
  char str[256] = "acos(0.43)";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = acos(0.43);
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

TEST(calc, calc_15) {
  char str[256] = "-2*ln(13)";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = -2 * log(13);
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

TEST(calc, calc_16) {
  char str[256] = "log(200.5)";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = log10(200.5);
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

TEST(calc, calc_17) {
  char str[256] = "5mod2+16mod2.5";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = 2;
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

TEST(calc, calc_18) {
  char str[256] = "-(-5)";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = 5;
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

TEST(calc, calc_19) {
  char str[256] = "-25-(-2)+(-(+3))";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = -25 - (-2) + (-(+3));
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

TEST(calc, calc_20) {
  char str[256] = "sin(x)-2*(-2)";
  double x = 3;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = sin(3) - 2 * (-2);
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

TEST(calc, calc_21) {
  char str[256] = "(-x)^2";
  double x = 3.52;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = pow((-3.52), 2);
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

TEST(calc, calc_22) {
  char str[256] = "()";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  ASSERT_EQ(status, 1);
}

TEST(calc, calc_23) {
  char str[256] = "()";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  ASSERT_EQ(status, 1);
}

TEST(calc, calc_24) {
  char str[256] = "12+(3+2)-2*5)";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  ASSERT_EQ(status, 1);
}

TEST(calc, calc_25) {
  char str[256] = "1.2+3-3.69.0";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  ASSERT_EQ(status, 1);
}

TEST(calc, calc_26) {
  char str[256] = "2/3++2";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  ASSERT_EQ(status, 1);
}

TEST(calc, calc_27) {
  char str[256] = "*2/2+1";
  double x = 0;
  s21::calcControl c(str, x);
  int status = c.verification();
  ASSERT_EQ(status, 1);
}

TEST(calc, calc_28) {
  char str[256] = "x*x";
  double x = 5.5;
  s21::calcControl c(str, x);
  int status = c.verification();
  double result = c.calculate();
  double correct = 5.5 * 5.5;
  ASSERT_EQ(status, 0);
  ASSERT_EQ(result, correct);
}

TEST(credit, annuitant) {
  double amount = 100000;
  double percent = 10;
  int period = 10;
  s21::creditControl c(amount, percent, period);
  c.annuitant();
  double monthly_payment = c.GetMonthlyPayment();
  double overpayment = c.GetOverpayment();
  double total_payment = c.GetTotalPayment();
  double test_monthly_payment = 10464.04;
  double test_overpayment = 4640.38;
  double test_total_payment = 104640.38;
  ASSERT_EQ(round(monthly_payment * 100) / 100, test_monthly_payment);
  ASSERT_EQ(round(overpayment * 100) / 100, test_overpayment);
  ASSERT_EQ(round(total_payment * 100) / 100, test_total_payment);
}

TEST(credit, differential) {
  double amount = 100000;
  double percent = 10;
  int period = 2;

  double monthly_payment = 0;
  double temp_amount = 0;
  int month = 0;
  s21::creditControl c(amount, percent, period);
  c.differential();
  double overpayment = round(c.GetOverpayment() * 100) / 100;
  double total_payment = c.GetTotalPayment();

  double test_overpayment = 1250;
  double test_total_payment = 101250;

  ASSERT_EQ(round(overpayment * 100) / 100, test_overpayment);
  ASSERT_EQ(total_payment, test_total_payment);
  c.print(&overpayment, &monthly_payment, &temp_amount, &month);
  ASSERT_EQ(round(overpayment * 100) / 100, 833.33);
  ASSERT_EQ(monthly_payment, 50000);
  ASSERT_EQ(round(temp_amount * 100) / 100, 50000);
  ASSERT_EQ(month, 1);
  c.print(&overpayment, &monthly_payment, &temp_amount, &month);
  ASSERT_EQ(round(overpayment * 100) / 100, 416.67);
  ASSERT_EQ(monthly_payment, 50000);
  ASSERT_EQ(round(temp_amount * 100) / 100, 0);
  ASSERT_EQ(month, 2);
  ASSERT_EQ(c.tableEmpty(), 1);
}

TEST(deposit, not_capitalization) {
  double deposit_amount = 100000;
  double percent = 10;
  double period = 2;
  double tax_rate = 13;
  int capitalization = 0;

  s21::depositControl d(deposit_amount, percent, period, tax_rate,
                        capitalization);

  double add_percent = 0;
  double balance_change = 0;
  double payment = 0;
  double temp_amount = 0;
  int date = 0;
  d.pushDate(1);
  d.pushDate(2);
  d.pushUp(1000, 1, 1);
  d.depositCalc();
  double accured_interest = round(d.GetAccuredInterest() * 100) / 100;
  double tax_amount = round(d.GetTaxAmount() * 100) / 100;
  ASSERT_EQ(accured_interest, 55.07);
  ASSERT_EQ(tax_amount, 7.16);
  ASSERT_EQ(d.GetDepositAmount(), 101000);
  d.printTable(&date, &add_percent, &balance_change, &payment, &temp_amount);
  ASSERT_EQ(round(add_percent * 100) / 100, 27.4);
  ASSERT_EQ(round(balance_change * 100) / 100, 1000);
  ASSERT_EQ(round(temp_amount * 100) / 100, 101000);
  ASSERT_EQ(round(payment * 100) / 100, 27.4);
  ASSERT_EQ(date, 1);
  d.printTable(&date, &add_percent, &balance_change, &payment, &temp_amount);
  ASSERT_EQ(round(add_percent * 100) / 100, 27.67);
  ASSERT_EQ(round(balance_change * 100) / 100, 0);
  ASSERT_EQ(round(temp_amount * 100) / 100, 101000);
  ASSERT_EQ(round(payment * 100) / 100, 27.67);
  ASSERT_EQ(date, 2);
}

TEST(deposit, capitalization) {
  double deposit_amount = 100000;
  double percent = 10;
  double period = 2;
  double tax_rate = 13;
  int capitalization = 1;

  s21::depositControl d(deposit_amount, percent, period, tax_rate,
                        capitalization);

  double add_percent = 0;
  double balance_change = 0;
  double payment = 0;
  double temp_amount = 0;
  int date = 0;
  d.pushDate(1);
  d.pushDate(2);
  d.pushDown(1000, 1, 1);
  d.depositCalc();
  double accured_interest = d.GetAccuredInterest();
  double tax_amount = d.GetTaxAmount();
  ASSERT_EQ(round(accured_interest * 100) / 100, 54.53);
  ASSERT_EQ(round(tax_amount * 100) / 100, 7.09);
  ASSERT_EQ(round(d.GetDepositAmount() * 100) / 100, 99054.53);
  d.printTable(&date, &add_percent, &balance_change, &payment, &temp_amount);
  ASSERT_EQ(round(add_percent * 100) / 100, 27.4);
  ASSERT_EQ(round(balance_change * 100) / 100, -972.6);
  ASSERT_EQ(round(temp_amount * 100) / 100, 99027.4);
  ASSERT_EQ(round(payment * 100) / 100, 1000);
  ASSERT_EQ(date, 1);
  d.printTable(&date, &add_percent, &balance_change, &payment, &temp_amount);
  ASSERT_EQ(round(add_percent * 100) / 100, 27.13);
  ASSERT_EQ(round(balance_change * 100) / 100, 27.13);
  ASSERT_EQ(round(temp_amount * 100) / 100, 99054.53);
  ASSERT_EQ(round(payment * 100) / 100, 0);
  ASSERT_EQ(date, 2);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
