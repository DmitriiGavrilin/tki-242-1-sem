
#pragma once

#include "Exercise.h"

#include <utility>

namespace miit::algebra {

class Task2 final : public Exercise {
public:
    explicit Task2(Matrix<int> matrix)
        : Exercise(std::move(matrix)) {}

    Task2(Matrix<int> matrix, Generator* generator)
        : Exercise(std::move(matrix), generator) {}

    Task2(Matrix<int> matrix, Generator& generator)
        : Task2(std::move(matrix), &generator) {}

    void solve() override;
};

}
