#include "matrix.h"

using namespace task;


Matrix::Matrix() {
    n_rows = 1;
    n_cols = 1;
    elms = new double*[1];
    elms[0] = new double[1];
    elms[0][0] = 1;
};

Matrix::Matrix(size_t rows, size_t cols) {
    n_rows = rows;
    n_cols = cols;
    elms = new double*[n_rows];
    for (size_t i = 0; i < n_rows; ++i)
        elms[i] = new double[n_cols];
    for (size_t i = 0; i < n_rows; ++i)
        for (size_t j = 0; j < n_cols; ++j)
            if (i == j) elms[i][j] = 1; else elms[i][j] = 0;
};

Matrix::~Matrix() {
    for (size_t i = 0; i < n_rows; ++i)
        delete [] this->elms[i];
    delete [] this->elms;
};

Matrix::Matrix(const Matrix& copy) {
    this->n_rows = copy.n_rows;
    this->n_cols = copy.n_cols;
    this->elms = new double*[this->n_rows];
    for (size_t i = 0; i < this->n_rows; ++i)
        this->elms[i] = new double[this->n_cols];
    for (size_t i = 0; i < this->n_rows; ++i)
        for (size_t j = 0; j < this->n_cols; ++j)
            this->elms[i][j] = copy.elms[i][j];
}

Matrix& Matrix::operator=(const Matrix& a){
    if (this == &a) return *this;
    for (size_t i = 0; i < this->n_rows; ++i)
        delete [] this->elms[i];
    delete [] this->elms;
    this->n_rows = a.n_rows;
    this->n_cols = a.n_cols;
    this->elms = new double*[this->n_rows];
    for (size_t i = 0; i < this->n_rows; ++i)
        this->elms[i] = new double[this->n_cols];
    for (size_t i = 0; i < this->n_rows; ++i)
        for (size_t j = 0; j < this->n_cols; ++j)
            this->elms[i][j] = a.elms[i][j];
    return *this;
}

double& Matrix::get(size_t row, size_t col){
    if ((row >= this->n_rows) || (col >= this->n_cols))
        throw OutOfBoundsException();
    return this->elms[row][col];
}

const double& Matrix::get(size_t row, size_t col) const {
    if ((row >= this->n_rows) || (col >= this->n_cols))
        throw OutOfBoundsException();
    return this->elms[row][col];
}

void Matrix::set(size_t row, size_t col, const double& value) {
    if ((row >= this->n_rows) || (col >= this->n_cols))
        throw OutOfBoundsException();
    this->elms[row][col] = value;
}

void Matrix::resize(size_t new_rows, size_t new_cols) {
    double** new_elms = new double*[new_rows];
    for (size_t i = 0; i < new_rows; ++i)
        new_elms[i] = new double[new_cols];
    for (size_t i = 0; i < new_rows; ++i)
        for (size_t j = 0; j < new_cols; ++j)
            if ((i < this->n_rows) & (j < this->n_cols)) {
                new_elms[i][j] = elms[i][j];
            } else new_elms[i][j] = 0;
    for (size_t i = 0; i < this->n_rows; ++i)
        delete [] this->elms[i];
    delete [] this->elms;
    this->elms = new_elms;
    this->n_rows = new_rows;
    this->n_cols = new_cols;
}

double* Matrix::operator[](size_t row) {
    if (row >= this->n_rows) throw SizeMismatchException();
    return this->elms[row];
}

double* Matrix::operator[](size_t row) const{
    if (row >= this->n_rows) throw SizeMismatchException();
    return this->elms[row];
}

Matrix& Matrix::operator+=(const Matrix& a){
    if ((this->n_rows != a.n_rows) || (this->n_cols != a.n_cols))
        throw SizeMismatchException();
    for (size_t i = 0; i < this->n_rows; ++i)
        for (size_t j = 0; j < this->n_cols; ++j)
            this->elms[i][j] += a.elms[i][j];
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& a){
    if ((this->n_rows != a.n_rows) || (this->n_cols != a.n_cols))
        throw SizeMismatchException();
    for (size_t i = 0; i < this->n_rows; ++i)
        for (size_t j = 0; j < this->n_cols; ++j)
            this->elms[i][j] -= a.elms[i][j];
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& a) {
    if (this->n_cols != a.n_rows) throw SizeMismatchException();
    double** new_elms = new double*[this->n_rows];
    for (size_t i = 0; i < this->n_rows; ++i)
        new_elms[i] = new double[a.n_cols];
    double res = 0;
    for (size_t i = 0; i < this->n_rows; ++i)
        for (size_t j = 0; j < a.n_cols; ++j) {
            res = 0;
            for (size_t k = 0; k < a.n_rows; ++k)
                res += this->elms[i][k] * a.elms[k][j];
            new_elms[i][j] = res;
        }
    for (size_t i = 0; i < this->n_rows; ++i)
        delete [] this->elms[i];
    delete [] this->elms;
    this->elms = new_elms;
    this->n_cols = a.n_cols;
    return *this;
}

Matrix& Matrix::operator*=(const double& number) {
    for (size_t i = 0; i < this->n_rows; ++i)
        for (size_t j = 0; j < this->n_cols; ++j)
            this->elms[i][j] *= number;
    return *this;
}

Matrix Matrix::operator+(const Matrix& a) const {
    if ((this->n_rows != a.n_rows) || (this->n_cols != a.n_cols))
        throw SizeMismatchException();
    Matrix res(this->n_rows, this->n_cols);
    for (size_t i = 0; i < this->n_rows; ++i)
        for (size_t j = 0; j < this->n_cols; ++j)
            res.elms[i][j] = this->elms[i][j] + a.elms[i][j];
    return res;
}

Matrix Matrix::operator-(const Matrix& a) const {
    if ((this->n_rows != a.n_rows) || (this->n_cols != a.n_cols))
        throw SizeMismatchException();
    Matrix res(this->n_rows, this->n_cols);
    for (size_t i = 0; i < this->n_rows; ++i)
        for (size_t j = 0; j < this->n_cols; ++j)
            res.elms[i][j] = this->elms[i][j] - a.elms[i][j];
    return res;
}

Matrix Matrix::operator*(const Matrix& a) const {
    if (this->n_cols != a.n_rows) throw SizeMismatchException();
    Matrix res(this->n_rows, a.n_cols);
    for (size_t i = 0; i < this->n_rows; ++i)
        for (size_t j = 0; j < a.n_cols; ++j) {
            res.elms[i][j] = 0;
            for (size_t k = 0; k < a.n_rows; ++k)
                res.elms[i][j] += this->elms[i][k] * a.elms[k][j];
        }
    return res;
}

Matrix Matrix::operator*(const double& a) const {
    Matrix res(this->n_rows, this->n_cols);
    for (size_t i = 0; i < this->n_rows; ++i)
        for (size_t j = 0; j < this->n_cols; ++j)
            res.elms[i][j] = this->elms[i][j] * a;
    return res;
}

Matrix Matrix::operator-() const {
    Matrix res(this->n_rows, this->n_cols);
    for (size_t i = 0; i < this->n_rows; ++i)
        for (size_t j = 0; j < this->n_cols; ++j)
            res.elms[i][j] = -this->elms[i][j];
    return res;
}

Matrix Matrix::operator+() const {
    Matrix res(this->n_rows, this->n_cols);
    for (size_t i = 0; i < this->n_rows; ++i)
        for (size_t j = 0; j < this->n_cols; ++j)
            res.elms[i][j] = +this->elms[i][j];
    return res;
}

double Matrix::det() const{
    if (this->n_cols != this->n_rows) throw SizeMismatchException();
    if (this->n_rows == 1) return this->elms[0][0];
    double res = 0;
    for (size_t k = 0; k < this->n_cols; ++k) {
        double gamma = this->elms[0][k];
        if ((k % 2) == 1) gamma = -gamma;
        Matrix sub(this->n_rows - 1, this->n_cols - 1);
        size_t i = 1;
        while (i < this->n_rows) {
            size_t jk = 0;
            for (size_t j = 0; j < this->n_rows; ++j)
                if (j != k) {
                    sub.elms[i - 1][jk] = this->elms[i][j];
                    ++jk;
                }
            ++i;
        }
        res += gamma * sub.det();
    }
    return res;
    return 0;
}

void Matrix::transpose() {
    double** new_elms = new double*[this->n_cols];
    for (size_t i = 0; i < this->n_cols; ++i)
        new_elms[i] = new double[this->n_rows];
    for (size_t i = 0; i < this->n_rows; ++i)
        for (size_t j = 0; j < this->n_cols; ++j)
            new_elms[j][i] = this->elms[i][j];
    for (size_t i = 0; i < this->n_rows; ++i)
        delete [] this->elms[i];
    delete [] this->elms;
    this->elms = new_elms;
    std::swap(this->n_cols, this->n_rows);
}

Matrix Matrix::transposed() const {
    Matrix res(this->n_cols, this->n_rows);
    for (size_t i = 0; i < this->n_rows; ++i)
        for (size_t j = 0; j < this->n_cols; ++j)
            res.set(j, i, this->elms[i][j]);
    return res;
}

double Matrix::trace() const{
    if (this->n_cols != this->n_rows) throw SizeMismatchException();
    double res = 0;
    for (size_t i = 0; i < this->n_rows; ++i) res += this->elms[i][i];
    return res;
}

std::vector<double> Matrix::getRow(size_t row){
    std::vector<double> vec;
    for (size_t i = 0; i < this->n_cols; ++i) vec.push_back(this->elms[row][i]);
    return vec;
}

std::vector<double> Matrix::getColumn(size_t column){
    std::vector<double> vec;
    for (size_t i = 0; i < this->n_rows; ++i) vec.push_back(this->elms[i][column]);
    return vec;
}

bool Matrix::operator==(const Matrix& a) const{
    if ((this->n_rows != a.n_rows) || (this->n_cols != a.n_cols))
        return false;
    for (size_t i = 0; i < this->n_rows; ++i)
        for (size_t j = 0; j < this->n_cols; ++j)
            if ((this->elms[i][j] > a.elms[i][j] + EPS) || (this->elms[i][j] < a.elms[i][j] - EPS))
                return false;
    return true;
}

bool Matrix::operator!=(const Matrix& a) const{
    if ((this->n_rows != a.n_rows) || (this->n_cols != a.n_cols))
        return true;
    for (size_t i = 0; i < this->n_rows; ++i)
        for (size_t j = 0; j < this->n_cols; ++j)
            if ((this->elms[i][j] > a.elms[i][j] + EPS) || (this->elms[i][j] < a.elms[i][j] - EPS))
                return true;
    return false;
}

std::pair<size_t, size_t> Matrix::getSize() const{
    std::pair<size_t, size_t> res = {this->n_rows, this->n_cols};
    return res;
}

Matrix task::operator*(const double& a, const Matrix& b){
    std::pair<size_t, size_t> size = b.getSize();
    Matrix res(size.first, size.second);
    for (size_t i = 0; i < size.first; ++i)
        for (size_t j = 0; j < size.second; ++j)
            res.set(i, j, b[i][j] * a);
    return res;
}

std::ostream& task::operator<<(std::ostream& output, const Matrix& matrix){
    std::pair<size_t, size_t> size = matrix.getSize();
    for (size_t i = 0; i < size.first; ++i)
        for (size_t j = 0; j < size.second; ++j) {
            output << matrix[i][j] << ' ';
        }
        output << '\n';
    return output;
}

std::istream& task::operator>>(std::istream& input, Matrix& matrix){
    uint32_t nrows, ncols;
    input >> nrows >> ncols;
    matrix.resize(nrows, ncols);
    for (size_t i = 0; i < nrows; ++i)
        for (size_t j = 0; j < ncols; ++j)
            input >> matrix[i][j];
    return input;
}
