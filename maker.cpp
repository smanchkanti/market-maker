#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

// Constants
const double INITIAL_PRICE = 100.0;
const double SPREAD = 1.0;
const double VOLATILITY = 0.1;
const double RISK_FREE_RATE = 0.05;

// Option struct
struct Option {
    string symbol;
    double strike;
    double expiry;
    double price;
};

// Function to generate random numbers from a normal distribution
double generateRandomNumber(double mean, double std_dev) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(mean, std_dev);
    return distribution(generator);
}

// Function to calculate the bid and ask prices based on the current mid price
void calculateBidAsk(double mid_price, double& bid_price, double& ask_price) {
    double half_spread = SPREAD / 2.0;
    bid_price = mid_price - half_spread;
    ask_price = mid_price + half_spread;
}

// Option pricing model - Black-Scholes
double blackScholes(double S, double K, double T, double r, double sigma, bool isCall) {
    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);

    if (isCall) {
        double call_price = S * exp(-r * T) * N(d1) - K * exp(-r * T) * N(d2);
        return call_price;
    } else {
        double put_price = K * exp(-r * T) * N(-d2) - S * exp(-r * T) * N(-d1);
        return put_price;
    }
}

// Cumulative standard normal distribution function
double N(double x) {
    return 0.5 * (1 + erf(x / sqrt(2)));
}

// Function to handle buy orders
void handleBuyOrder(const Option& option, double bid_price) {
    cout << "Buy Order: " << option.symbol << " Strike: " << option.strike << " Expiry: " << option.expiry << " Price: " << bid_price << endl;
    // Add buy order handling logic here
}

// Function to handle sell orders
void handleSellOrder(const Option& option, double ask_price) {
    cout << "Sell Order: " << option.symbol << " Strike: " << option.strike << " Expiry: " << option.expiry << " Price: " << ask_price << endl;
    // Add sell order handling logic here
}

int main() {
    double current_price = INITIAL_PRICE;

    cout << "Market Maker Simulation" << endl;
    cout << "Initial Price: " << current_price << endl;

    // Generate a list of options
    vector<Option> options{
        {"AAPL", 120.0, 0.25, 0.0},
        {"GOOG", 2000.0, 0.5, 0.0},
        {"MSFT", 150.0, 0.75, 0.0},
        {"AMZN", 3000.0, 1.0, 0.0}
    };

    // Simulate market maker behavior for 10 iterations
    for (int i = 1; i <= 10; ++i) {
        // Generate a random price change based on volatility
        double price_change = generateRandomNumber(0.0, VOLATILITY);

        // Calculate the new mid price
        double mid_price = current_price + price_change;

        // Calculate bid and ask prices
        double bid_price, ask_price;
        calculateBidAsk(mid_price, bid_price, ask_price);

        // Update the current price for the next iteration
        current_price = mid_price;

        // Update option prices using the Black-Scholes model
        for (auto& option : options) {
            option.price = blackScholes(current_price, option.strike, option.expiry, RISK_FREE_RATE, VOLATILITY, true);
        }

        // Sort options by price in ascending order
        sort(options.begin(), options.end(), [](const Option& a, const Option& b) {
            return a.price < b.price;
        });

        // Handle buy and sell orders for options
        for (const auto& option : options) {
            handleBuyOrder(option, bid_price);
            handleSellOrder(option, ask_price);
        }

        // Output the current market information
        cout << "Iteration " << i << endl;
        cout << "Mid Price: " << mid_price << endl;
        cout << "Bid Price: " << bid_price << endl;
        cout << "Ask Price: " << ask_price << endl;
        cout << "Options: " << endl;
        for (const auto& option : options) {
            cout << option.symbol << " Price: " << option.price << endl;
        }
        cout << endl;
    }

    return 0;
}
