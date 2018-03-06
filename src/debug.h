//
// Created by Ted Klein Bergman on 3/6/18.
//

#ifndef OPENGLPROJECT_DEBUG_H
#define OPENGLPROJECT_DEBUG_H


#define ASSERT(condition, message, args...) _assertion((bool)(condition), message, #condition, __FILE__, __LINE__, ##args)
void _assertion(bool condition, const char* message, const char* condition_string, const char* file_name, int line, ...);


#endif //OPENGLPROJECT_DEBUG_H
