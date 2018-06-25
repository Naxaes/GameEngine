//
// Created by Ted Klein Bergman on 3/6/18.
//

#ifndef OPENGLPROJECT_DEBUG_H
#define OPENGLPROJECT_DEBUG_H


/*
 * The variadic arguments are arguments for a C-styled formatted message. For example:
 *     ASSERT(1 == 2, "This is not right, %s! Go back to %s.", name, school);
 *
 * */


#define ASSERT(condition, message, args...) Implementation::assertion((bool)(condition), message, #condition, __FILE__, __LINE__, ##args)

namespace Implementation
{
    void assertion(bool condition, const char* message,
                   const char* condition_string, const char* file_name, int line, ...);
}


#endif //OPENGLPROJECT_DEBUG_H
