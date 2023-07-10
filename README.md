# Options Market Maker

This project is an implementation of an Options Market Maker program that simulates the behavior of a market maker in the financial options market. The program uses the Black-Scholes option pricing model, random price generation, and includes AI-based volatility prediction using LSTM neural networks.

## Features

1. **Option Market Making**: The program acts as a market maker for options, handling buy and sell orders.
2. **Black-Scholes Model**: The program uses the Black-Scholes option pricing model to calculate option prices based on the current market conditions.
3. **Random Price Generation**: The program generates random price changes based on the given volatility.
4. **Volatility Prediction**: The program includes an AI-based volatility prediction model trained using LSTM neural networks to forecast future volatility.
5. **P&L Calculation**: The program tracks profit and loss (P&L) for both options and futures.

## Dependencies

- C++ Standard Library
- LibTorch (C++ PyTorch library)

## Usage

1. Ensure you have the required dependencies installed.
2. Compile the program using a C++ compiler with the necessary flags and include paths for LibTorch.
3. Run the compiled executable.

## File Structure

- `maker.cpp`: The main source file containing the options market maker program.
- `volatility_data.csv`: CSV file containing historical volatility data for training the volatility prediction model.

## Training the Volatility Prediction Model

To train the volatility prediction model, follow these steps:

1. Prepare a CSV file containing historical volatility data. Each row should represent a time step, and each column should represent a feature or input to the model.
2. Update the `volatility_data.csv` file with your historical volatility data.
3. Ensure LibTorch is properly installed and configured.
4. Compile and run the program. During execution, the program will load the training data, train the volatility prediction model, and save the trained model weights.


