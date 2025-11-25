#include <gtest/gtest.h>
#include <cmath>
#include "../LoanCalculator.h"

// Test normal EMI calculation
TEST(LoanTests, NormalEMI)
{
    LoanCalculator calc;
    calc.setAmount(100000.0);
    calc.setInterest(7.5);
    calc.setPeriodTotal(360);

    double emi = calc.calculatePayment();

    // Approximate expected EMI
    EXPECT_NEAR(emi, 699.0, 1.0);
}

// Test invalid input handling
TEST(LoanTests, InvalidInput)
{
    LoanCalculator calc;

    calc.setAmount(-5000.0);  // negative amount
    calc.setInterest(5.0);
    calc.setPeriodTotal(12);

    EXPECT_THROW(calc.calculatePayment(), std::invalid_argument);
}

// Test large tenure for overflow or instability
TEST(LoanTests, LargeTenureNoOverflow)
{
    LoanCalculator calc;
    calc.setAmount(50000.0);
    calc.setInterest(8.0);
    calc.setPeriodTotal(1000);

    double emi = calc.calculatePayment();

    // EMI should be positive and finite
    EXPECT_GT(emi, 0);
    EXPECT_TRUE(std::isfinite(emi));
}
