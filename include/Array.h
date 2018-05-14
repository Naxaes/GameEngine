//
// Created by Ted Klein Bergman on 3/30/18.
//

#ifndef OPENGLPROJECT_ARRAY_H
#define OPENGLPROJECT_ARRAY_H

#include <utility>
#include <array>
#include <vector>
#include <iterator>


using index_t = unsigned long;


template <typename T, index_t n>
class Array
{
private:
    T data[n] = {};

public:
    Array() = default;

    Array(const T& array[static n])
    {
        for (index_t i = 0; i < n; i++)
            data[i] = array[i];
    }

    Array(const std::array<T, n>& array)
    {
        for (index_t i = 0; i < n; i++)
            data[i] = array[i];
    }

    Array(std::array<T, n>& array)
    {
        std::move(array.begin(), array.end(), std::begin(data));
    }

    Array(const std::vector<T>& array)
    {
        for (index_t i = 0; i < n; i++)
            data[i] = array[i];
    }

    Array(std::vector<T>& array)
    {
        std::move(array.begin(), array.end(), std::begin(data));
    }

};



#endif //OPENGLPROJECT_ARRAY_H
