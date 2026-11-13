#pragma once

#include "Exercise.h"

#include <utility>

namespace miit::algebra {

class Task1 final : public Exercise {
public:
    Task1(
        Matrix<int> matrix,
        const Generator& generator
    )
        : Exercise(std::move(matrix), generator) {}

    void solve() override;
};

}
