#include <iostream>
#include <random>

using namespace std;

double generateRandomPrice(double mean, double std_dev) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(mean, std_dev);
    return distribution(generator);
}

int main() {
    double natural_gas_price = 3.0;
    double oil_price = 60.0;

    double natural_gas_volatility = 0.15;
    double oil_volatility = 0.25;

    double natural_gas_price_change = generateRandomPrice(0.0, natural_gas_volatility);
    double oil_price_change = generateRandomPrice(0.0, oil_volatility);

    double natural_gas_new_price = natural_gas_price + natural_gas_price_change;
    double oil_new_price = oil_price + oil_price_change;

    cout << "Natural Gas Price: " << natural_gas_new_price << endl;
    cout << "Oil Price: " << oil_new_price << endl;

    return 0;
}
