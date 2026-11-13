#pragma once

#include "Exercise.h"

#include <utility>

namespace miit::algebra {

class Task2 final : public Exercise {
public:
    Task2(
        Matrix<int> matrix,
        const Generator& generator
    )
        : Exercise(std::move(matrix), generator) {}

    void solve() override;
};

}
