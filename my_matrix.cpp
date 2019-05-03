#include <vector>
#include <iostream>

template <typename T>
class Matrix;
template <typename T>
class MatrixIter {
private:
    Matrix<T>& matrix;
    size_t row;
    size_t column;

public:
    MatrixIter(
            Matrix<T>& m, size_t r, size_t c) : matrix(m), row(r), column(c) {
    }
    bool operator == (const MatrixIter& other) const {
        return row == other.row && column == other.column;
    }
    bool operator != (const MatrixIter& other) const {
        return !(*this == other);
    }
    T& operator * () const {
        return matrix[row][column];
    }
    MatrixIter& operator ++() {
        if (column != matrix.size().second - 1) {
            ++column;
        } else {
            ++row;
            column = 0;
        }
        return *this;
    }
    const MatrixIter operator ++(int) {
        MatrixIter old = *this;
        ++(*this);
        return old;
    }
};

template <typename T>
class Matrix;
template <typename T>
class Const_MatrixIter {
private:
    const Matrix<T>& matrix;
    size_t row;
    size_t column;

public:
    Const_MatrixIter(
            const Matrix<T>& m, size_t r, size_t c) : matrix(m), row(r), column(c) {
    }
    bool operator == (const Const_MatrixIter& other) const {
        return row == other.row && column == other.column;
    }
    bool operator != (const Const_MatrixIter& other) const {
        return !(*this == other);
    }
    const T& operator * () const {
        return matrix[row][column];
    }
    Const_MatrixIter& operator ++() {
        if (column != matrix.size().second - 1) {
            ++column;
        } else {
            ++row;
            column = 0;
        }
        return *this;
    }
    const Const_MatrixIter operator ++(int) {
        MatrixIter old = *this;
        ++(*this);
        return old;
    }
};

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> rows;

public:
    explicit Matrix(const std::vector<std::vector<T>>& r) {
        rows = r;
    }
    const std::pair<size_t, size_t> size() const {
        if (rows.empty()) {
            return {0, 0};
        }
        return {rows.size(), rows[0].size()};
    }
    const std::vector<T>& operator[](size_t num) const {
        return rows[num];
    }
    std::vector<T>& operator[](size_t num) {
        return rows[num];
    }
    Matrix<T>& operator +=(const Matrix<T>& other) {
        for (size_t i = 0; i < size().first; ++i) {
            for (size_t j = 0; j < size().second; ++j) {
                rows[i][j] += other[i][j];
            }
        }
        return *this;
    }
    Matrix<T> operator +(const Matrix<T>& other) const {
        std::vector<std::vector<T>> new_rows = rows;
        for (size_t i = 0; i < size().first; ++i) {
            for (size_t j = 0; j < size().second; ++j) {
                new_rows[i][j] += other[i][j];
            }
        }
        return Matrix(new_rows);
    }
    template <typename lambda>
    Matrix<T>& operator *=(const lambda& l) {
        for (size_t i = 0; i < size().first; ++i) {
            for (size_t j = 0; j < size().second; ++j) {
                rows[i][j] *= l;
            }
        }
        return *this;
    }
    template <typename lambda>
    Matrix<T> operator *(const lambda& l) const {
        std::vector<std::vector<T>> new_rows = rows;
        for (size_t i = 0; i < size().first; ++i) {
            for (size_t j = 0; j < size().second; ++j) {
                new_rows[i][j] *= l;
            }
        }
        return Matrix(new_rows);
    }
    Matrix<T>& transpose() {
        // input: Matrix mxn; output: Matrix nxm
        std::vector<std::vector<T>> new_rows;
        size_t m = size().first, n = size().second;
        new_rows.resize(n);
        for (auto& row : new_rows) {
            row.resize(m);
        }
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                new_rows[j][i] = rows[i][j];
            }
        }
        rows = new_rows;
        return *this;
    }
    Matrix<T> transposed() const {
        std::vector<std::vector<T>> new_rows;
        size_t m = size().first, n = size().second;
        new_rows.resize(n);
        for (auto& row : new_rows) {
            row.resize(m);
        }
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                new_rows[j][i] = rows[i][j];
            }
        }
        return Matrix(new_rows);
    }
    Matrix<T> operator *(const Matrix<T>& other) const {
        if (!rows.empty() && !other.rows.empty()) {
            assert(size().second == other.size().first);
            std::vector<std::vector<T>> res;
            res.resize(size().first);
            for (auto& row : res) {
                row.resize(other.size().second);
            }
            for (size_t i = 0; i < size().first; ++i) {
                for (size_t j = 0; j < other.size().second; ++j) {
                    for (size_t k = 0; k < size().second; ++k) {
                        res[i][j] +=    rows[i][k] * other.rows[k][j];
                    }
                }
            }
            return Matrix(res);
        }
        return *this;
    }
    Matrix<T>& operator *=(const Matrix<T>& other) {
        if (!rows.empty() && !other.rows.empty()) {
            assert(size().second == other.size().first);
            std::vector<std::vector<T>> res;
            res.resize(size().first);
            for (auto& row : res) {
                row.resize(other.size().second);
            }
            for (size_t i = 0; i < size().first; ++i) {
                for (size_t j = 0; j < other.size().second; ++j) {
                    for (size_t k = 0; k < size().second; ++k) {
                        res[i][j] +=    rows[i][k] * other.rows[k][j];
                    }
                }
            }
            rows = res;
        }
        return *this;
    }

    MatrixIter<T> begin() {
        return MatrixIter(*this, 0, 0);
    }
    MatrixIter<T> end() {
        return MatrixIter(*this, size().first, 0);
    }
    Const_MatrixIter<T> begin() const {
        return Const_MatrixIter(*this, 0, 0);
    }
    Const_MatrixIter<T> end() const {
        return Const_MatrixIter(*this, size().first, 0);
    }
};

template <typename T>
std::ostream& operator<< (std::ostream& out, const Matrix<T>& m) {
    for (size_t i = 0; i < (m.size()).first; ++i) {
        if (i != 0) {
            out << '\n';
        }
        for (size_t j = 0; j < m.size().second; ++j) {
            if (j != 0) {
                out << '\t';
            }
            out << m[i][j];
        }
    }
    return out;
}

