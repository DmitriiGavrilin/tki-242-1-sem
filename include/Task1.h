
#pragma once

#include "Exercise.h"

#include <utility>

namespace miit::algebra {

class Task1 final : public Exercise {
public:
    explicit Task1(Matrix<int> matrix)
        : Exercise(std::move(matrix)) {}

    Task1(
        Matrix<int> matrix,
        const Generator& generator
    )
        : Exercise(std::move(matrix), generator) {}

    // Совместимость со старыми тестами.
    Task1(
        Matrix<int> matrix,
        const Generator* generator
    )
        : Exercise(std::move(matrix), generator) {}

    void solve() override;
};

}