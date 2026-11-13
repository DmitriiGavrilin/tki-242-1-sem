
#include "Exercise.h"

#include <stdexcept>
#include <utility>

namespace miit::algebra {

Exercise::Exercise(Matrix<int> matrix)
    : matrix_(std::move(matrix)),
      generator_(nullptr) {}

Exercise::Exercise(
    Matrix<int> matrix,
    const Generator& generator
)
    : Exercise(std::move(matrix), &generator) {}

Exercise::Exercise(
    Matrix<int> matrix,
    const Generator* generator
)
    : matrix_(std::move(matrix)),
      generator_(generator) {}

Exercise::~Exercise() = default;

void Exercise::fill() {
    if (generator_ == nullptr) {
        throw std::logic_error("Exercise has no generator");
    }

    matrix_.fill(*generator_);
}

Matrix<int> Exercise::getMatrix() const {
    return matrix_;
}

}