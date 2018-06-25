//
// Created by Ted Klein Bergman on 3/28/18.
//

#ifndef OPENGLPROJECT_COMPONENT_DISPLACEMENT_H
#define OPENGLPROJECT_COMPONENT_DISPLACEMENT_H


#include <glm/glm.hpp>

#include "component.h"


class DisplacementComponent : public Component
{
public:
    glm::vec3 location;
    glm::vec3 rotation;
    glm::vec3 scale;

    DisplacementComponent(Entity* entity, glm::vec3 location, glm::vec3 rotation, glm::vec3 scale) :
            Component(entity), location(location), rotation(rotation), scale(scale) {}
    ~DisplacementComponent() = default;

    void update(float dt) override {};
};

#endif //OPENGLPROJECT_COMPONENT_DISPLACEMENT_H
