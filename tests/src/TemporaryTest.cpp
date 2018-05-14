//
// Created by Ted Klein Bergman on 3/15/18.
//

#include "TemporaryTest.h"
#if RUN_TEMPORARYTEST

#include <utility>
#include <array>
#include <vector>
#include <iterator>
#include <cassert>


using index_t = unsigned long;


template <typename T, index_t n>
class Array
{
private:
    T data[n] = {};

public:
    index_t size() { return n; }

    T& operator[] (index_t index)
    {
        assert(index < n);
        return data[index];
    }

};


int main()
{

    return 0;
}


#endif