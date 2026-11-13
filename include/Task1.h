
#pragma once

#include "Exercise.h"

#include <utility>

namespace miit::algebra {

class Task1 final : public Exercise {
public:
    explicit Task1(Matrix<int> matrix)
        : Exercise(std::move(matrix)) {}

    Task1(Matrix<int> matrix, Generator* generator)
        : Exercise(std::move(matrix), generator) {}

    Task1(Matrix<int> matrix, Generator& generator)
        : Task1(std::move(matrix), &generator) {}

    void solve() override;
};

}
