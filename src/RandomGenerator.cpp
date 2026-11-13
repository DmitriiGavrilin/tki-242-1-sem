#include "RandomGenerator.h"

#include <stdexcept>

namespace miit::algebra {
namespace {

int validateMinimum(int minimum, int maximum) {
    if (minimum > maximum) {
        throw std::invalid_argument(
            "Minimum must not exceed maximum"
        );
    }

    return minimum;
}

}

RandomGenerator::RandomGenerator(int minimum, int maximum)
    : engine_(std::random_device{}()),
    distribution_(validateMinimum(minimum, maximum), maximum) {}

int RandomGenerator::generate() const {
    return distribution_(engine_);
}

}