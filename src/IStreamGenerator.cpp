#include "IStreamGenerator.h"

#include <stdexcept>

namespace miit::algebra {

IStreamGenerator::IStreamGenerator(std::istream& input)
    : input_(input) {}

int IStreamGenerator::generate() const {
    int value = 0;

    if (!(input_ >> value)) {
        throw std::runtime_error(
            "Failed to read a matrix value"
        );
    }

    return value;
}

}