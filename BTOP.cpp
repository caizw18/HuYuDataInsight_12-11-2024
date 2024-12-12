#include <iostream>
#include <vector>
#include <cmath>

double binomialOptionPrice(double S, double K, double r, double T, double sigma, int steps, bool isCall) {
    double dt = T / steps;
    double u = std::exp(sigma * std::sqrt(dt));
    double d = 1 / u;
    double p = (std::exp(r * dt) - d) / (u - d);
    double discountFactor = std::exp(-r * dt);

    std::vector<double> prices(steps + 1);
    std::vector<double> optionValues(steps + 1);

    for (int i = 0; i <= steps; ++i) {
        prices[i] = S * std::pow(u, steps - i) * std::pow(d, i);
        optionValues[i] = isCall ? std::max(prices[i] - K, 0.0) : std::max(K - prices[i], 0.0);
    }

    for (int step = steps - 1; step >= 0; --step) {
        for (int i = 0; i <= step; ++i) {
            optionValues[i] = discountFactor * (p * optionValues[i] + (1 - p) * optionValues[i + 1]);
        }
    }

    return optionValues[0];
}

int main() {
    double S = 100, K = 100, r = 0.05, T = 1.0, sigma = 0.2;
    int steps = 100;
    bool isCall = true;

    double price = binomialOptionPrice(S, K, r, T, sigma, steps, isCall);
    std::cout << "Binomial Option Price: " << price << std::endl;

    return 0;
}