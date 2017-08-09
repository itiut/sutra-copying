double amortize(double amt, double rate, double inflation, int months,
                int selloff_month, double extra_payoff, int verbose,
                double *interest_pv, double *duration, double *monthly_payment);

typedef struct {
    double amount, years, rate, selloff_year, extra_payoff, inflation;
    int months, selloff_month;
    _Bool show_table;
    double interest, interest_pv, monthly_payment, years_to_payoff;
    char *err;
} amortization_s;

#define amortization(...) amortize_prep((amortization_s){.show_table=1, __VA_ARGS__})

amortization_s amortize_prep(amortization_s in);
