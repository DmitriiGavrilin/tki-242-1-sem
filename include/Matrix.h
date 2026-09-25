#pragma once

#include "Generator.h"

#include <algorithm>
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace miit::algebra {

template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data_;

    void validateRectangular() const {
        if (data_.empty()) return;
        const std::size_t width = data_.front().size();
        for (const auto& row : data_) {
            if (row.size() != width) throw std::invalid_argument("Matrix rows must have equal length");
        }
    }

public:
    Matrix() = default;
    Matrix(std::size_t rows, std::size_t columns, const T& value = T{})
        : data_(rows, std::vector<T>(columns, value)) {}
    explicit Matrix(const std::vector<std::vector<T>>& values) : data_(values) { validateRectangular(); }
    Matrix(const Matrix&) = default;
    Matrix(Matrix&&) noexcept = default;
    ~Matrix() = default;
    Matrix& operator=(const Matrix&) = default;
    Matrix& operator=(Matrix&&) noexcept = default;

    std::vector<T>& operator[](std::size_t row) {
        return data_[row];
    }

    const std::vector<T>& operator[](std::size_t row) const {
        return data_[row];
    }

    Matrix operator<<(std::size_t positions) const {
        Matrix result(*this);
        for (auto& row : result.data_) {
            if (!row.empty()) {
                const std::size_t shift = positions % row.size();
                std::rotate(row.begin(), row.begin() + static_cast<std::ptrdiff_t>(shift), row.end());
            }
        }
        return result;
    }

    Matrix operator>>(std::size_t positions) const {
        Matrix result(*this);
        for (auto& row : result.data_) {
            if (!row.empty()) {
                const std::size_t shift = positions % row.size();
                std::rotate(row.rbegin(), row.rbegin() + static_cast<std::ptrdiff_t>(shift), row.rend());
            }
        }
        return result;
    }

    std::size_t rows() const noexcept { return data_.size(); }
    std::size_t columns() const noexcept { return data_.empty() ? 0U : data_.front().size(); }
    bool empty() const noexcept { return rows() == 0U || columns() == 0U; }

    void fill(Generator& generator) {
        for (auto& row : data_) for (auto& value : row) value = static_cast<T>(generator.generate());
    }

    void insertRow(std::size_t index, const std::vector<T>& row) {
        if (index > rows()) throw std::out_of_range("Row insertion index is out of range");
        if (!data_.empty() && row.size() != columns()) throw std::invalid_argument("Inserted row has wrong size");
        data_.insert(data_.begin() + static_cast<std::ptrdiff_t>(index), row);
    }

    void removeRow(std::size_t index) {
        if (index >= rows()) throw std::out_of_range("Row removal index is out of range");
        data_.erase(data_.begin() + static_cast<std::ptrdiff_t>(index));
    }

    void insertColumn(std::size_t index, const std::vector<T>& column) {
        if (empty()) throw std::logic_error("Cannot insert a column into an empty matrix");
        if (index > columns()) throw std::out_of_range("Column insertion index is out of range");
        if (column.size() != rows()) throw std::invalid_argument("Inserted column has wrong size");
        for (std::size_t row = 0; row < rows(); ++row) {
            data_[row].insert(data_[row].begin() + static_cast<std::ptrdiff_t>(index), column[row]);
        }
    }

    void removeColumn(std::size_t index) {
        if (index >= columns()) throw std::out_of_range("Column removal index is out of range");
        for (auto& row : data_) row.erase(row.begin() + static_cast<std::ptrdiff_t>(index));
    }

    std::string toString() const {
        std::ostringstream out;
        for (std::size_t row = 0; row < rows(); ++row) {
            for (std::size_t column = 0; column < columns(); ++column) {
                if (column != 0U) out << ' ';
                out << data_[row][column];
            }
            if (row + 1U != rows()) out << '\n';
        }
        return out.str();
    }
};

} // namespace miit::algebra
