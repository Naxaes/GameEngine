//
// Created by Ted Klein Bergman on 3/6/18.
//

#include "debug.h"

#include <iostream>

void _assertion(bool condition, const char* message, const char* condition_string, const char* file_name, int line, ...)
{
    if (!condition)
    {
        char* new_message = new char[sizeof(char) * 256];
        strcpy(new_message, message);

        char buffer[sizeof(char) * 2048];
        va_list argptr;
        va_start(argptr, line);
        vsprintf(buffer, new_message, argptr);
        va_end(argptr);

        fprintf(
                stderr,
                "[Assertion Error]:\n\tMessage:   %s\n\tCondition: %s\n\tFile:      %s\n\tLine:      %i\n",
                buffer, condition_string, file_name, line
        );
        exit(-1);
    }
}