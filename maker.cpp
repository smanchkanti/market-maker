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
    int quantity;
};

// Future struct
struct Future {
    string symbol;
    double expiry;
    double price;
    int quantity;
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

// Function to handle buy orders for options
void handleBuyOrder(const Option& option, double bid_price, double& optionsPnL) {
    cout << "Buy Option Order: " << option.symbol << " Strike: " << option.strike << " Expiry: " << option.expiry << " Price: " << bid_price << endl;
    // Add buy order handling logic for options here

    double pnl = (option.price - bid_price) * option.quantity;
    optionsPnL += pnl;
}

// Function to handle sell orders for options
void handleSellOrder(const Option& option, double ask_price, double& optionsPnL) {
    cout << "Sell Option Order: " << option.symbol << " Strike: " << option.strike << " Expiry: " << option.expiry << " Price: " << ask_price << endl;
    // Add sell order handling logic for options here

    double pnl = (ask_price - option.price) * option.quantity;
    optionsPnL += pnl;
}

// Function to handle buy orders for futures
void handleBuyOrder(const Future& future, double bid_price, double& futuresPnL) {
    cout << "Buy Future Order: " << future.symbol << " Expiry: " << future.expiry << " Price: " << bid_price << endl;
    // Add buy order handling logic for futures here

    double pnl = (future.price - bid_price) * future.quantity;
    futuresPnL += pnl;
}

// Function to handle sell orders for futures
void handleSellOrder(const Future& future, double ask_price, double& futuresPnL) {
    cout << "Sell Future Order: " << future.symbol << " Expiry: " << future.expiry << " Price: " << ask_price << endl;
    // Add sell order handling logic for futures here

    double pnl = (ask_price - future.price) * future.quantity;
    futuresPnL += pnl;
}

int main() {
    double current_price = INITIAL_PRICE;

    cout << "Market Maker Simulation" << endl;
    cout << "Initial Price: " << current_price << endl;

    // Generate a list of options
    vector<Option> options{
        {"AAPL", 120.0, 0.25, 0.0, 0},
        {"GOOG", 2000.0, 0.5, 0.0, 0},
        {"MSFT", 150.0, 0.75, 0.0, 0},
        {"AMZN", 3000.0, 1.0, 0.0, 0}
    };

    // Generate a list of futures contracts
    vector<Future> futures{
        {"CL", 1.0, 0.0, 0},
        {"ES", 1.0, 0.0, 0},
        {"NQ", 1.0, 0.0, 0},
        {"GC", 1.0, 0.0, 0}
    };

    // Variables to track PnL
    double optionsPnL = 0.0;
    double futuresPnL = 0.0;

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

        // Update future prices
        for (auto& future : futures) {
            future.price = current_price;  // Example: Use current price as futures price
        }

        // Sort options by price in ascending order
        sort(options.begin(), options.end(), [](const Option& a, const Option& b) {
            return a.price < b.price;
        });

        // Handle buy and sell orders for options
        for (const auto& option : options) {
            handleBuyOrder(option, bid_price, optionsPnL);
            handleSellOrder(option, ask_price, optionsPnL);
        }

        // Handle buy and sell orders for futures
        for (const auto& future : futures) {
            handleBuyOrder(future, bid_price, futuresPnL);
            handleSellOrder(future, ask_price, futuresPnL);
        }

        // Output the current market information and PnL
        cout << "
