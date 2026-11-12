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

enum class FillChoice {
    Keyboard = 1,
    Random,
    Zeros,
    Constant
};

enum class ActionChoice {
    Exit = 0,
    Task1 = 1,
    Task2,
    Both
};

template<typename T>
T readValue(const char* prompt) {
    bool success = false;
    while (!success) {
        std::cout << prompt;
        T value{};
        if (std::cin >> value) return value;
        if (std::cin.eof()) throw std::runtime_error("Input ended");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid value. Try again.\n";
    }
    return T{};
}

int main() {
    try {
        std::size_t rows = 0U;
        std::size_t columns = 0U;
        while (rows == 0U) rows = readValue<std::size_t>("Rows (> 0): ");
        while (columns == 0U) columns = readValue<std::size_t>("Columns (> 0): ");

        std::cout << "Fill: 1 - keyboard, 2 - random, 3 - zeros, 4 - constant\n";
        const auto fillChoice = static_cast<FillChoice>(readValue<int>("Choice: "));
        std::unique_ptr<Generator> generator;
        
        switch (fillChoice) {
        case FillChoice::Keyboard:
            std::cout << "Enter " << rows * columns << " integers:\n";
            generator = std::make_unique<IStreamGenerator>(std::cin);
            break;
        case FillChoice::Random: {
            const int minimum = readValue<int>("Minimum: ");
            const int maximum = readValue<int>("Maximum: ");
            generator = std::make_unique<RandomGenerator>(minimum, maximum);
            break;
        }
        case FillChoice::Zeros:
            generator = std::make_unique<ZeroGenerator>();
            break;
        case FillChoice::Constant:
            generator = std::make_unique<ConstantGenerator>(readValue<int>("Constant: "));
            break;
        default:
            std::cerr << "Unknown fill method\n";
            return 1;
        }

        Matrix<int> original(rows, columns);
        original.fill(*generator);
        std::cout << "Initial matrix:\n" << original.toString() << '\n';

        bool running = true;
        while (running) {
            std::cout << "\n0 - exit, 1 - first transformation, 2 - second transformation, 3 - both\n";
            const auto action = static_cast<ActionChoice>(readValue<int>("Action: "));
            
            switch (action) {
            case ActionChoice::Exit:
                running = false;
                break;
            case ActionChoice::Task1: {
                Task1 task(original);
                task.solve();
                std::cout << "Task 1 result:\n" << task.getMatrix().toString() << '\n';
                break;
            }
            case ActionChoice::Task2: {
                Task2 task(original);
                task.solve();
                std::cout << "Task 2 result:\n" << task.getMatrix().toString() << '\n';
                break;
            }
            case ActionChoice::Both: {
                Task1 task1(original);
                task1.solve();
                std::cout << "Task 1 result:\n" << task1.getMatrix().toString() << '\n';

                Task2 task2(original);
                task2.solve();
                std::cout << "Task 2 result:\n" << task2.getMatrix().toString() << '\n';
                break;
            }
            default:
                std::cout << "Unknown action\n";
                break;
            }
        }
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
