#include <iostream>
#include <vector>
#include <string>
#include "Matrix.hpp"
using namespace std;
using namespace zich;

namespace zich
{
    /* constructor for the matrix */
    Matrix::Matrix(vector<double> v, int row, int col)
    {
        if (row < 1 || col < 1)
        {
            throw std::invalid_argument("you can't create a matrix smaller then 1X1");
        }
        if (size(v) != row * col)
        {
            throw std::invalid_argument("you can't create a matrix with those values");
        }

        this->v = {v.begin(), v.end()};
        this->row = row;
        this->col = col;
    }

    /* make one matrix get the parametes of the other */
    // void Matrix::operator=(const Matrix &temp)
    // {
    //     this->v = temp.v;
    //     this->row = temp.row;
    //     this->col = temp.col;
    // }

    /* add one matrix to another and return the new matrix */
    Matrix Matrix::operator+(const Matrix &second)
    {

        if (this->col != second.col || this->row != second.row)
        {
            throw std::invalid_argument("you can't add differet nXm matrix's");
        }
        Matrix copy = *this;
        for (size_t i = 0; i < size(this->v); i++)
        {
            copy.v[i] += second.v[i];
        }
        return copy;
    }
    /* unary plus - nothing happend to the matrix */
    Matrix &Matrix::operator+()
    {
        return *this;
    }

    /* add to the first matrix the second, and return the first after adding the numbers of matrix 2 */
    void Matrix::operator+=(const Matrix &second)
    {
        if (this->col != second.col || this->row != second.row)
        {
            throw std::invalid_argument("you can't decrease differet nXm matrix's");
        }
        for (size_t i = 0; i < size(this->v); i++)
        {
            this->v[i] += second.v[i];
        }
    }

    /* increasing the matrix by 1 and return the matrix after we add to it */
    Matrix &Matrix::operator++()
    {
        for (size_t i = 0; i < size(this->v); i++)
        {
            this->v[i] += 1;
        }
        return *this;
    }

    /* create a copy of the matrix, add to the matrix and return the copy */
    Matrix Matrix::operator++(int num) const
    {
        Matrix copy = *this;
        for (size_t i = 0; i < size(this->v); i++)
        {
            copy.v[i] += 1;
        }
        return copy;
    }

    /* decrease one matrix from another and return the new matrix */
    Matrix Matrix::operator-(const Matrix &second)
    {
        if (this->col != second.col || this->row != second.row)
        {
            throw std::invalid_argument("you can't decrease differet nXm matrix's");
        }
        Matrix copy = *this;
        for (size_t i = 0; i < size(this->v); i++)
        {
            copy.v[i] -= second.v[i];
        }
        return copy;
    }

    /* unary minus - all the values of the matrix is multiple in -1 */
    Matrix Matrix::operator-()
    {
        Matrix copy = *this;
        for (size_t i = 0; i < size(this->v); i++)
        {
            copy.v[i] *= -1;
        }
        return copy;
    }
    /* decrease from the first matrix the second, and return the first after decreasing  the numbers of matrix 2 */
    void Matrix::operator-=(const Matrix &second)
    {
        if (this->col != second.col || this->row != second.row)
        {
            throw std::invalid_argument("you can't decrease differet nXm matrix's");
        }
        for (size_t i = 0; i < size(this->v); i++)
        {
            this->v[i] -= second.v[i];
        }
    }

    /*  decreasing the matrix by 1 and return the matrix after we remove from it */
    Matrix &Matrix::operator--()
    {
        for (size_t i = 0; i < size(this->v); i++)
        {
            this->v[i] -= 1;
        }
        return *this;
    }

    /* create a copy of the matrix, remove from the matrix and return the copy */
    Matrix Matrix::operator--(int num) const
    {
        Matrix copy = *this;
        for (size_t i = 0; i < size(this->v); i++)
        {
            copy.v[i] -= 1;
        }
        return copy;
    }

    /* multiply one matrix with another */
    Matrix Matrix::operator*(const Matrix &second)
    {
        if (this->col != second.row)
        {
            throw std::invalid_argument("you can't multiply matrix that has differet nXm mXt m size");
        }
        Matrix copy = Matrix(this->v, this->row, second.col);
        size_t copy_row = size_t(copy.row);
        size_t copy_col = size_t(copy.col);

        for (size_t i = 0; i < copy_row; i++)
        {
            for (size_t j = 0; j < copy_col; j++)
            {
                for (size_t k = 0; k < copy_col; k++)
                {
                    copy.v[i * copy_col + j] += this->v[i * copy_col + k] * second.v[k * copy_col + j];
                }
            }
        }

        return copy;
    }

    /* multiply one matrix in a double number */
    Matrix operator*(double num, const Matrix &current)
    {
        Matrix copy = current;
        for (size_t i = 0; i < size(current.v); i++)
        {
            copy.v[i] *= num;
        }
        return copy;
    }

    /* multiply one matrix in a double number */
    Matrix Matrix::operator*(double num) const
    {
        Matrix copy = *this;
        for (size_t i = 0; i < size(this->v); i++)
        {
            copy.v[i] *= num;
        }
        return copy;
    }

    /* multiply one matrix in a double number and add to it */
    void Matrix::operator*=(double num)
    {
        for (size_t i = 0; i < size(this->v); i++)
        {
            this->v[i] *= num;
        }
    }

    /* matrix first is equal to matrix second */
    bool Matrix::operator==(const Matrix &second) const
    {
        if (this->col != second.col || this->row != second.row)
        {
            return false;
        }
        if (size(this->v) != size(second.v))
        {
            return false;
        }
        for (size_t i = 0; i < size(this->v); i++)
        {
            if (this->v[i] != second.v[i])
            {
                return false;
            }
        }
        return true;
    }

    /* matrix first is not equal to matrix second */
    bool Matrix::operator!=(const Matrix &second) const
    {
        Matrix temp = *this;
        bool check = temp == second;
        return check;
    }

    /* matrix first is bigger then matrix second */
    bool Matrix::operator>(const Matrix &second) const
    {
        if (this->col != second.col || this->row != second.row)
        {
            throw std::invalid_argument("you can't decrease differet nXm matrix's");
        }
        double sum_this = 0;
        double sum_second = 0;

        for (size_t i = 0; i < size(this->v); i++)
        {
            sum_this += this->v[i];
            sum_second += second.v[i];
        }
        return sum_this > sum_second;
    }

    /* matrix first is bigger-equal from matrix second */
    bool Matrix::operator>=(const Matrix &second) const
    {
        Matrix temp = *this;
        bool equal = temp == second;
        bool bigger = temp > second;
        return equal || bigger;
    }

    /* matrix first is smaller then matrix second */
    bool Matrix::operator<(const Matrix &other) const
    {
        if (this->col != other.col || this->row != other.row)
        {
            throw std::invalid_argument("you can't decrease differet nXm matrix's");
        }
        double sum_this = 0;
        double sum_second = 0;

        for (size_t i = 0; i < size(this->v); i++)
        {
            sum_this += this->v[i];
            sum_second += other.v[i];
        }
        return sum_this < sum_second;
    }

    /* matrix first is smaller-equal from matrix second */
    bool Matrix::operator<=(const Matrix &other) const
    {
        Matrix temp = *this;
        bool equal = temp == other;
        bool smaller = temp < other;
        return equal || smaller;
    }

    std::ostream &operator<<(std::ostream &output, const Matrix &m)
    {

        size_t final_row = size_t(m.row);
        size_t final_col = size_t(m.col);

        for (size_t i = 0; i < final_row; i++)
        {
            output << '[';
            for (size_t j = 0; j < final_col; j++)
            {
                output << m.v[(i * final_row) + final_col] + ' ';
            }
            output << ']';
            output << '\n';
        }
        return output;
    }
    std::istream &operator>>(std::istream &input, Matrix &m)
    {
        return input;
    }
}
