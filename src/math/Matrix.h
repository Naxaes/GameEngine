//
// Created by Ted Klein Bergman on 3/10/18.
//

#ifndef OPENGLPROJECT_MATRIX_H
#define OPENGLPROJECT_MATRIX_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <array>
#include <tuple>

template <typename T, unsigned int count>
std::array<std::tuple<T, T>, count> zip(T* array1, T* array2)
{
    std::array<std::tuple<T, T>, count> result;
    for (unsigned int i = 0; i < count; i++)
        result[i] = std::make_tuple(array1[i], array2[i]);
    return result;
};



template <typename T, unsigned int count>
class Vector
{
private:
    T data[count] = {0};

public:

    Vector() = default;

    explicit Vector(T fill)
    {
        for (T& value : data)
            value = fill;
    }

//    explicit Vector(T values[static count])
//    {
//        for (unsigned int i = 0; i < count; i++)
//            data[i] = values[i];
//    }

    Vector<T, count> elementwise_multiplication(Vector<T, count> other)
    {
        Vector<T, count> result;
        for (unsigned int i = 0; i < count; i++)
            result.data[i] = data[i] * other.data[i];
        return result;
    };

    double dot(Vector<T, count> other) const
    {
        double result = 0;
        for (unsigned int i = 0; i < count; i++)
            result += data[i] * other.data[i];
        return result;
    };

    double length() const
    {
        return std::sqrt(length_squared());
    }

    double length_squared() const
    {
        double length = 0;
        for (T value : data)
            length += value * value;
        return length;
    }

    double distance(Vector<T, count>& other) const
    {
        return std::sqrt(distance_squared(other));
    }

    double distance_squared(Vector<T, count>& other) const
    {
        double distance = 0;
        for (unsigned int i = 0; i < count; i++)
            distance += std::abs(data[i] - other.data[i]);
        return distance;
    }

    unsigned int count1() const
    {
        return count;
    }

    unsigned int size() const
    {
        return sizeof(T) * count;
    }

    // Functions for iteration.
    T* begin()
    {
        return &data[0];
    }

    T* end()
    {
        return &data[count];
    }


    // START: VECTOR OVERLOAD
    friend Vector<T, count> operator + (const Vector<T, count>& vector1, const Vector<T, count>& vector2)
    {
        Vector<T, count> result;
        for (unsigned int i = 0; i < count; i++)
            result.data[i] = vector1.data[i] + vector2.data[i];
        return result;
    }

    friend Vector<T, count> operator + (T value, const Vector<T, count>& vector)
    {
        Vector<T, count> result;
        for (unsigned int i = 0; i < count; i++)
            result.data[i] = vector.data[i] + value;
        return result;
    }

    friend Vector<T, count> operator + (const Vector<T, count>& vector, T value)
    {
        Vector<T, count> result;
        for (unsigned int i = 0; i < count; i++)
            result.data[i] = vector.data[i] + value;
        return result;
    }

    friend Vector<T, count> operator - (const Vector<T, count>& vector1, const Vector<T, count>& vector2)
    {
        Vector<T, count> result;
        for (unsigned int i = 0; i < count; i++)
            result.data[i] = vector1.data[i] - vector2.data[i];
        return result;
    }

    friend Vector<T, count> operator - (T value, const Vector<T, count>& vector)
    {
        Vector<T, count> result;
        for (unsigned int i = 0; i < count; i++)
            result.data[i] = vector.data[i] - value;
        return result;
    }

    friend Vector<T, count> operator - (const Vector<T, count>& vector, T value)
    {
        Vector<T, count> result;
        for (unsigned int i = 0; i < count; i++)
            result.data[i] = vector.data[i] - value;
        return result;
    }

    friend Vector<T, count> operator * (const Vector<T, count>& vector, T value)
    {
        Vector<T, count> result;
        for (unsigned int i = 0; i < count; i++)
            result.data[i] = vector.data[i] * value;
        return result;
    }

    friend Vector<T, count> operator * (T value, const Vector<T, count>& vector)
    {
        Vector<T, count> result;
        for (unsigned int i = 0; i < count; i++)
            result.data[i] = vector.data[i] * value;
        return result;
    }

    friend std::ostream& operator << (std::ostream& os, const Vector<T, count>& vector)
    {
        os << "[";
        os << std::fixed << std::setprecision(2);
        for (T value : vector.data)
            os << std::left << std::setw(6) << value;
        os << "]" << std::endl;
        return os;
    }
    // END: VECTOR OVERLOAD

};




template <typename T, unsigned int rows, unsigned int cols>
class Matrix
{
public:
    constexpr static unsigned int count = rows * cols;

private:
    T data[count] = {0};

public:

    Matrix() = default;
    explicit Matrix(T value)
    {
        for (T& element : *this)
            element = value;
    }

    T& operator () (unsigned int row, unsigned int col)
    {
        return data[row * rows + col];
    }

    Matrix<T, rows, cols> operator + (T value)
    {
        Matrix<T, rows, cols> result;
        for (unsigned int row = 0; row < rows; row++)
            for (unsigned int col = 0; col < cols; col++)
                result(row, col) = this->operator()(row, col) + value;
        return result;
    }

    Matrix<T, rows, cols> operator + (Matrix<T, rows, cols>& matrix)
    {
        Matrix<T, rows, cols> result;
        for (unsigned int row = 0; row < rows; row++)
            for (unsigned int col = 0; col < cols; col++)
                result(row, col) = this->operator()(row, col) + matrix(row, col);
        return result;
    }

    void operator += (T value)
    {
        for (unsigned int row = 0; row < rows; row++)
            for (unsigned int col = 0; col < cols; col++)
                this->operator()(row, col) += value;
    }

    void operator += (Matrix<T, rows, cols>& matrix)
    {
        for (unsigned int row = 0; row < rows; row++)
            for (unsigned int col = 0; col < cols; col++)
                this->operator()(row, col) += matrix(row, col);
    }

    Matrix<T, rows, cols> operator * (Matrix<T, rows, cols>& matrix)
    {
        Matrix<T, rows, cols> result;
        for (unsigned int row = 0; row < rows; row++)
            for (unsigned int col = 0; col < cols; col++)
            {
                T value = 0;
                for (unsigned int j = 0, i = 0; j < rows && i < cols; j++, i++)
                    value += this->operator()(row, i) + matrix(j, col);
                result(row, col) = value;
            }
        return result;
    }

    void operator *= (Matrix<T, rows, cols>& matrix)
    {
        for (unsigned int row = 0; row < rows; row++)
            for (unsigned int col = 0; col < cols; col++)
            {
                for (unsigned int j = 0, i = 0; j < rows && i < cols; j++, i++)
                    this->operator()(row, i) += matrix(j, col);
            }
    }

    friend std::ostream& operator << (std::ostream& os, Matrix<T, rows, cols>& matrix)
    {
        os << "Matrix:\n";
        for (unsigned int row = 0; row < rows; row++)
        {
            os << "\t";
            for (unsigned int col = 0; col < cols; col++)
                os << std::left << std::setw(7) << matrix(row, col);
            os << "\n";
        }
        return os;
    }


    // Functions for iteration.
    T* begin()
    {
        return &data[0];
    }

    T* end()
    {
        return &data[count];
    }
};


#endif //OPENGLPROJECT_MATRIX_H
