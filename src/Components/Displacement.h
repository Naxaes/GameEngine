//
// Created by Ted Klein Bergman on 3/28/18.
//

#ifndef OPENGLPROJECT_DISPLACEMENT_H
#define OPENGLPROJECT_DISPLACEMENT_H


#include <glm/glm.hpp>

#include "../Entity.h"


class DisplacementComponent : public Component
{
public:

    glm::vec3 location;
    glm::vec3 rotation;
    glm::vec3 scale;

    DisplacementComponent(const Entity& entity, glm::vec3 location, glm::vec3 rotation, glm::vec3 scale) :
            Component(entity), location(location), rotation(rotation), scale(scale) {}
    ~DisplacementComponent() = default;

    void update(
            float x  = 0.0f, float y  = 0.0f, float z  = 0.0f,
            float rx = 0.0f, float ry = 0.0f, float rz = 0.0f,
            float sx = 0.0f, float sy = 0.0f, float sz = 0.0f
    )
    {
        if (!x)
            return;

        location.x += x;
        location.y += y;
        location.z += z;

        rotation.x += rx;
        rotation.y += ry;
        rotation.z += rz;

        scale.x += sx;
        scale.y += sy;
        scale.z += sz;
    };
};

#endif //OPENGLPROJECT_DISPLACEMENT_H
