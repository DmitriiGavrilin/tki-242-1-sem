
#include "Task1.h"

#include <algorithm>

namespace miit::algebra {

void Task1::solve() {
    for (std::size_t r = 0; r < matrix_.rows(); ++r) {
        if (matrix_[r].empty()) {
            continue;
        }

        const int maximum = *std::max_element(
            matrix_[r].begin(),
            matrix_[r].end()
        );

        for (int& value : matrix_[r]) {
            if (value == maximum) {
                value = 0;
            }
        }
    }
}

}
