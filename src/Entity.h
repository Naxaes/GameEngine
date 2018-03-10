//
// Created by Ted Klein Bergman on 3/6/18.
//

#ifndef OPENGLPROJECT_ENTITY_H
#define OPENGLPROJECT_ENTITY_H


#include <glad/glad.h>
#include <vector>
#include <array>
#include <bitset>
#include <cassert>



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









constexpr unsigned int MAX_COMPONENTS = 32;

class Entity;
class Component;

static inline unsigned int generate_component_id() noexcept
{
    static unsigned int id{0u};
    return id++;
}

template <typename T> static inline unsigned int get_component_id() noexcept
{
    static_assert(std::is_base_of<Component, T>(), "Component must be inherited from Component.");
    static unsigned int id{generate_component_id()};
    return id;
}


class Component
{
private:
    const Entity& entity;

public:
    explicit Component(const Entity& entity) : entity(entity) {}
    virtual void update() {}
    virtual ~Component() = default;
};



class Entity
{
private:
    std::vector<std::shared_ptr<Component>> components;
    std::array<std::shared_ptr<Component>, MAX_COMPONENTS> component_array;
    std::bitset<MAX_COMPONENTS> component_mask;

public:

    explicit Entity() = default;

    ~Entity() = default;  // Everything is cleaned up by vector with smart pointers.

    template <typename T, typename... TemplateArgs> void add_component(TemplateArgs&&... args)
    {
        unsigned int id = get_component_id<T>();

        std::shared_ptr<Component> component{new T(*this, std::forward<TemplateArgs>(args)...)};

        component_mask[id] = true;
        components.push_back(component);
        component_array[id] = component;
    }

    template <typename T> bool has_component() const
    {
        unsigned int id = get_component_id<T>();
        return component_mask[id];
    }

    template <typename T> T& get_component() const
    {
        unsigned int id = get_component_id<T>();
        assert(has_component<T>());
        return *static_cast<T*>(component_array[id].get());  // Will throw error if component isn't publicly inherited.
    }

    void update() const
    {
        for (const std::shared_ptr<Component>& component : components)
            component->update();
    }
};














#endif //OPENGLPROJECT_ENTITY_H
