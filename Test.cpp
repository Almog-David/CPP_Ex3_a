#include "doctest.h"
#include "Matrix.hpp"
#include <string>
using namespace zich;
using namespace std;

TEST_CASE("good inputs")
{

    std::vector<double> vec1 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    std::vector<double> vec2 = {2, 0, 2, 0};
    std::vector<double> vec3 = {-1, 0, 0, 0, -1, 0, 0, 0, -1};

    /*creating a valid matrix */
    CHECK_NOTHROW(Matrix(vec1, 3, 3));
    CHECK_NOTHROW(Matrix(vec1, 1, 9));
    CHECK_NOTHROW(Matrix(vec2, 2, 2));
    CHECK_NOTHROW(Matrix(vec2, 4, 1));
    CHECK_NOTHROW(Matrix(vec3, 3, 3));
    CHECK_NOTHROW(Matrix(vec3, 9, 1));

    /* math operators on matrix's */
    std::vector<double> vec5 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    std::vector<double> vec6 = {2, 0, 2, 0};
    std::vector<double> vec7 = {0, 3, 0, 3};
    std::vector<double> vec8 = {-1, 0, 0, 0, -1, 0, 0, 0, -1};
    Matrix matrix = Matrix(vec5, 3, 3);
    Matrix matrix2 = Matrix(vec6, 2, 2);
    Matrix matrix3 = Matrix(vec7, 2, 2);
    Matrix matrix4 = Matrix(vec8, 3, 3);
    CHECK_NOTHROW(matrix + matrix4);
    CHECK_NOTHROW(matrix3 += matrix2);
    CHECK_NOTHROW(matrix4 - matrix);
    CHECK_NOTHROW(bool ans = (matrix2 > matrix3));
    CHECK_NOTHROW(bool ans = (matrix <= matrix4));
    CHECK_NOTHROW(bool ans = (matrix != matrix4));
    CHECK_NOTHROW(bool ans = (matrix2 == matrix3));
    CHECK_NOTHROW(matrix * 5);

    // /* checking the input of the math operators */
    // Matrix m = matrix2 + matrix3;
    // std::vector<double> ans1 = {2, 3, 2, 3};
    // CHECK(m.v == ans1);
    // Matrix x = matrix + matrix4;
    // std::vector<double> ans2 = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    // CHECK(x.v == ans2);
    // Matrix y = matrix4 - matrix;
    // std::vector<double> ans3 = {-2, 0, 0, 0, -2, 0, 0, 0, -2};
    // CHECK(y.v == ans3);
}

TEST_CASE("bad input")
{
    std::vector<double> vec9 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    std::vector<double> vec10 = {2, 0, 0, 0, 2, 0, 0, 0, 2};

    /* invalid numbers - negetiv or zero number when creating the matrix */
    CHECK_THROWS(Matrix(vec9, -1, 2));
    CHECK_THROWS(Matrix(vec9, 3, 0));
    CHECK_THROWS(Matrix(vec10, 0, 0));
    CHECK_THROWS(Matrix(vec10, 0, -4));

    /* invalid numbers - can't create a matrix in this size */
    CHECK_THROWS(Matrix(vec9, 4, 1));
    CHECK_THROWS(Matrix(vec9, 3, 2));
    CHECK_THROWS(Matrix(vec10, 6, 6));
    CHECK_THROWS(Matrix(vec10, 1, 1));

    /* invalid numbers - can't do operators on matrix's with different sizes (mXn)*/
    Matrix matrix1 = Matrix(vec9, 3, 3);
    Matrix matrix2 = Matrix(vec9, 1, 9);
    Matrix matrix3 = Matrix(vec9, 9, 1);
    CHECK_THROWS(matrix1 + matrix2);
    CHECK_THROWS(matrix1 += matrix2);
    CHECK_THROWS(matrix1 - matrix2);
    CHECK_THROWS(matrix1 -= matrix2);
    CHECK_THROWS(matrix1 * matrix2);
    CHECK_THROWS(matrix3 + matrix2);
    CHECK_THROWS(matrix1 += matrix3);
    CHECK_THROWS(matrix3 - matrix1);
    CHECK_THROWS(matrix2 -= matrix1);
    CHECK_THROWS(matrix3 * matrix1);
}
