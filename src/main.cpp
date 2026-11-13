#include "ConstantGenerator.h"
#include "IStreamGenerator.h"
#include "RandomGenerator.h"
#include "Task1.h"
#include "Task2.h"
#include "ZeroGenerator.h"

#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

using namespace miit::algebra;

template<typename T>
T readValue(const char* prompt) {
    while (true) {
        std::cout << prompt;

        T value{};

        if (std::cin >> value) {
            return value;
        }

        if (std::cin.eof()) {
            throw std::runtime_error("Input ended");
        }

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );

        std::cout << "Invalid value. Try again.\n";
    }
}

int main() {
    try {
        std::size_t rows = 0U;
        std::size_t columns = 0U;

        while (rows == 0U) {
            rows = readValue<std::size_t>("Rows (> 0): ");
        }

        while (columns == 0U) {
            columns = readValue<std::size_t>("Columns (> 0): ");
        }

        std::cout
            << "Fill: 1 - keyboard, 2 - random, "
            << "3 - zeros, 4 - constant\n";

        int fillChoice = readValue<int>("Choice: ");

        while (fillChoice < 1 || fillChoice > 4) {
            std::cout << "Invalid choice. Enter a number from 1 to 4.\n";
            fillChoice = readValue<int>("Choice: ");
        }

        std::unique_ptr<Generator> generator;

        switch (fillChoice) {
        case 1:
            std::cout << "Enter " << rows * columns << " integers:\n";
            generator = std::make_unique<IStreamGenerator>(std::cin);
            break;

        case 2: {
            const int minimum = readValue<int>("Minimum: ");
            const int maximum = readValue<int>("Maximum: ");

            if (minimum > maximum) {
                throw std::invalid_argument(
                    "Minimum cannot be greater than maximum"
                );
            }

            generator = std::make_unique<RandomGenerator>(
                minimum,
                maximum
            );
            break;
        }

        case 3:
            generator = std::make_unique<ZeroGenerator>();
            break;

        case 4:
            generator = std::make_unique<ConstantGenerator>(
                readValue<int>("Constant: ")
            );
            break;

        default:
            throw std::logic_error("Unexpected fill choice");
        }

        Matrix<int> original(rows, columns);
        original.fill(*generator);

        std::cout << "Initial matrix:\n"
                  << original.toString() << '\n';

        bool running = true;

        while (running) {
            std::cout
                << "\n0 - exit, 1 - first transformation, "
                << "2 - second transformation, 3 - both\n";

            int action = readValue<int>("Action: ");

            while (action < 0 || action > 3) {
                std::cout << "Invalid action. Enter a number from 0 to 3.\n";
                action = readValue<int>("Action: ");
            }

            switch (action) {
            case 0:
                running = false;
                break;

            case 1: {
                Task1 task(original, *generator);
                task.solve();

                std::cout << "Task 1 result:\n"
                          << task.getMatrix().toString() << '\n';
                break;
            }

            case 2: {
                Task2 task(original, *generator);
                task.solve();

                std::cout << "Task 2 result:\n"
                          << task.getMatrix().toString() << '\n';
                break;
            }

            case 3: {
                Task1 task1(original, *generator);
                task1.solve();

                std::cout << "Task 1 result:\n"
                          << task1.getMatrix().toString() << '\n';

                Task2 task2(original, *generator);
                task2.solve();

                std::cout << "Task 2 result:\n"
                          << task2.getMatrix().toString() << '\n';
                break;
            }

            default:
                throw std::logic_error("Unexpected action");
            }
        }

    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
