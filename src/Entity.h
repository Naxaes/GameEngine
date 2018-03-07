//
// Created by Ted Klein Bergman on 3/6/18.
//

#ifndef OPENGLPROJECT_ENTITY_H
#define OPENGLPROJECT_ENTITY_H


#include <glad/glad.h>


struct Displacement
{
    GLfloat x, y, z;
    GLfloat rx, ry, rz;
    GLfloat sx, sy, sz;
};

struct Movement
{
    GLfloat dx, dy, dz;
    GLfloat rx, ry, rz;
    GLfloat sx, sy, sz;
};

struct Graphics
{
    // Render same texture first, then same model.

    Displacement* displacement;
    unsigned int model;   // VAO
    unsigned int vertex_count;
    unsigned int texture;
};


struct World
{
    Displacement* entity_displacement;
    Movement* entity_movement;
    Graphics* entity_graphics;

    unsigned int entity_count = 0;
    unsigned int max_count = 0;

    explicit World(unsigned int max_count) : max_count(max_count)
    {
        entity_displacement = new Displacement[max_count];
        entity_movement = new Movement[max_count];
        entity_graphics = new Graphics[max_count];
    }

    unsigned int entity_create(Displacement displacement, Movement movement, Graphics graphics)
    {
        if (entity_count >= max_count)
        {
            return 0;
        }

        entity_displacement[entity_count] = displacement;
        entity_movement[entity_count] = movement;
        entity_graphics[entity_count] = graphics;

        unsigned int ID = entity_count++;
        return ID;
    }
};

#endif //OPENGLPROJECT_ENTITY_H
