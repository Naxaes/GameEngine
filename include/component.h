//
// Created by Ted Klein Bergman on 5/14/18.
//

#ifndef OPENGLPROJECT_COMPONENT_H
#define OPENGLPROJECT_COMPONENT_H

#include <type_traits>

class Entity;

class Component
{
public:
    explicit Component(Entity* entity) {};
    virtual void update(float dt) = 0;
};


inline unsigned int generate_component_id() noexcept
{
    static unsigned int id{0u};
    return id++;
}

template <typename T>
inline unsigned int get_component_id() noexcept
{
    static_assert(std::is_base_of<Component, T>(), "Component must be inherited from Component.");
    static unsigned int id{generate_component_id()};
    return id;
}



#endif //OPENGLPROJECT_COMPONENT_H
