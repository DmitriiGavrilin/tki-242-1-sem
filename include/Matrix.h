
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

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data_;

    void validateRectangular() const {
        if (data_.empty()) {
            return;
        }

        const std::size_t expectedColumns = data_[0].size();

        for (const auto& row : data_) {
            if (row.size() != expectedColumns) {
                throw std::invalid_argument(
                    "Matrix rows must have equal length"
                );
            }
        }
    }

public:
    Matrix() = default;

    Matrix(std::size_t rows, std::size_t columns)
        : data_(rows, std::vector<T>(columns)) {}

    explicit Matrix(const std::vector<std::vector<T>>& data)
        : data_(data) {
        validateRectangular();
    }

    explicit Matrix(std::vector<std::vector<T>>&& data)
        : data_(std::move(data)) {
        validateRectangular();
    }

    Matrix(const Matrix&) = default;
    Matrix(Matrix&&) noexcept = default;

    Matrix& operator=(const Matrix&) = default;
    Matrix& operator=(Matrix&&) noexcept = default;

    virtual ~Matrix() = default;

    std::size_t rows() const {
        return data_.size();
    }

    std::size_t columns() const {
        return data_.empty() ? 0 : data_[0].size();
    }

    bool empty() const {
        return data_.empty() || data_[0].empty();
    }

    std::vector<T>& operator[](std::size_t index) {
        return data_.at(index);
    }

    const std::vector<T>& operator[](std::size_t index) const {
        return data_.at(index);
    }

    void fill(const Generator& generator) {
        for (auto& row : data_) {
            for (auto& value : row) {
                value = static_cast<T>(generator.generate());
            }
        }
    }

    void shiftLeft() {
        for (auto& row : data_) {
            if (!row.empty()) {
                std::rotate(row.begin(), row.begin() + 1, row.end());
            }
        }
    }

    void shiftRight() {
        for (auto& row : data_) {
            if (!row.empty()) {
                std::rotate(row.rbegin(), row.rbegin() + 1, row.rend());
            }
        }
    }

    void insertRow(std::size_t index, const std::vector<T>& row) {
        if (index > rows()) {
            throw std::out_of_range("Invalid row index");
        }

        if (!data_.empty() && row.size() != columns()) {
            throw std::invalid_argument("Invalid row size");
        }

        if (data_.empty() && !row.empty()) {
            for (const auto& existingRow : data_) {
                if (existingRow.size() != row.size()) {
                    throw std::invalid_argument("Invalid row size");
                }
            }
        }

        data_.insert(data_.begin() + index, row);
    }

    void removeRow(std::size_t index) {
        if (index >= rows()) {
            throw std::out_of_range("Invalid row index");
        }

        data_.erase(data_.begin() + index);
    }

    void insertColumn(std::size_t index, const std::vector<T>& column) {
        if (index > columns()) {
            throw std::out_of_range("Invalid column index");
        }

        if (column.size() != rows()) {
            throw std::invalid_argument("Invalid column size");
        }

        for (std::size_t r = 0; r < rows(); ++r) {
            data_[r].insert(data_[r].begin() + index, column[r]);
        }
    }

    void removeColumn(std::size_t index) {
        if (index >= columns()) {
            throw std::out_of_range("Invalid column index");
        }

        for (auto& row : data_) {
            row.erase(row.begin() + index);
        }
    }

    std::string toString() const {
        std::ostringstream output;

        for (const auto& row : data_) {
            for (std::size_t c = 0; c < row.size(); ++c) {
                if (c > 0) {
                    output << ' ';
                }

                output << row[c];
            }

            output << '\n';
        }

        return output.str();
    }
};

}