//
// Created by Ted Klein Bergman on 3/10/18.
//

#include "MatrixTest.h"
#if RUN_MATRIX_TEST


#include <iostream>


#include "../src/math/Matrix.h"
#include "../src/debug.h"


void test_addition()
{

}


void test_iteration()
{
    for (unsigned int i = 1; i < 5; i++)
    {
        unsigned int index = 0;
        Matrix<float, 4, 4> matrix{2};
        for (float& x : matrix)
            x = index++;

        index = 0;
        for (float x : matrix)
            ASSERT(x == index++, "");
    }
}




int main()
{

    Vector<float, 4> vector;
    std::cout << vector << std::endl;

    Vector<float, 4> vector1(0.353456346f);
    std::cout << vector1 << std::endl;




    test_addition();
    test_iteration();

    Matrix<float, 4, 4> matrix1{};

    std::cout << matrix1 << std::endl;

    int index = 0;
    for (unsigned int row = 0; row < 4; row++)
        for (unsigned int col = 0; col < 4; col++)
            matrix1(row, col) = index++;

    std::cout << matrix1 << std::endl;


    Matrix<float, 4, 4> matrix2{4};
    std::cout << matrix2 << std::endl;


    Matrix<float, 4, 4> matrix3 = matrix1 + matrix2;
    std::cout << matrix3 << std::endl;

    Matrix<float, 4, 4> matrix4 = matrix1 * matrix3;
    std::cout << matrix4 << std::endl;

}






#endif