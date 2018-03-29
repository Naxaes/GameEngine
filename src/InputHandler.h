//
// Created by Ted Klein Bergman on 3/17/18.
//

// http://gameprogrammingpatterns.com/command.html

#ifndef OPENGLPROJECT_INPUTHANDLER_H
#define OPENGLPROJECT_INPUTHANDLER_H

#include "Entity.h"

class Command
{
public:
    virtual ~Command() = default;
    virtual void execute(Entity& entity) = 0;
    virtual void redo(Entity& entity) = 0;
};


class RotateCommand : Command
{
public:
    void execute(Entity& entity) override
    {
    }

    void redo(Entity& entity) override
    {

    }
};



#endif //OPENGLPROJECT_INPUTHANDLER_H
