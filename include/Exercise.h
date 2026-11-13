#pragma once

#include "Generator.h"
#include "Matrix.h"

namespace miit::algebra {

class Exercise {
protected:
    Matrix<int> matrix_;
    const Generator* generator_;

public:
    explicit Exercise(
        Matrix<int> matrix,
        const Generator& generator
    );

    virtual ~Exercise();

    virtual void solve() = 0;

    void fill();

    Matrix<int> getMatrix() const;
};

}
