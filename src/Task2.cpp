#include "Task2.h"
#include <algorithm>
#include <vector>
namespace miit::algebra {
namespace {

}
void Task2::solve() {
    if (matrix_.empty()) return;
    const std::size_t originalRows = matrix_.rows();
    std::vector<int> zeros(matrix_.columns(), 0);
    for (std::size_t r = originalRows; r-- > 0U;) if (matrix_[r][0] % 3 == 0) matrix_.insertRow(r, zeros);
}
}
