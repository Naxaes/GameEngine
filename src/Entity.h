//
// Created by Ted Klein Bergman on 3/6/18.
//

#ifndef OPENGLPROJECT_ENTITY_H
#define OPENGLPROJECT_ENTITY_H

#include <vector>
#include <array>
#include <bitset>

#include <glad/glad.h>

#include "debug.h"

using ComponentArrayID = unsigned int;
using ComponentID = unsigned int;
using EntityID = unsigned int;

class Entity;
class Component;
class ComponentManager;

constexpr static unsigned int MAX_NUMBER_COMPONENTS = 32;

static inline unsigned int generate_component_id() noexcept
{
    static unsigned int id{0u};
    return id++;
}

template <typename T>
static inline unsigned int get_component_id() noexcept
{
    static_assert(std::is_base_of<Component, T>(), "Component must be inherited from Component.");
    static unsigned int id{generate_component_id()};
    return id;
}


class Component
{
public:
    // Takes a const reference, so Entity must have const methods.
    // No component should be able to add components, which they can't with a const reference since that method isn't
    // const. However, asking if an entity has an component or retrieving components is okay.
    explicit Component(const Entity& entity) {}
    virtual ~Component() = default;

    // All components should have an update! However, since each component could take different amounts of parameters,
    // it's not possible to have a virtual update method.
//    virtual void update() {}
};


class ComponentManager
{
private:
    std::array<void*, MAX_NUMBER_COMPONENTS> components{nullptr};
    std::bitset<MAX_NUMBER_COMPONENTS> component_mask{0};


    std::vector<Entity> entities;  // Return index in create_entity();


public:

    // TODO(ted): Maybe take MAX_NUMBER_COMPONENTS as a parameter in the constructor? Then we could create multiple
    // managers, each having their own set of components (like ParticleManager, StaticManager, ...).
    // Of course, the the get_component_id function have to change (maybe just put them as manager methods).

    ComponentManager() = default;
    ~ComponentManager()
    {
        for (auto &component : components)
            delete component;
    }

    template <typename T, typename... TemplateArgs>
    T* add_component(TemplateArgs&&... args)  // TODO(ted): What kind of pointer to return?
    {
        unsigned int id = get_component_id<T>();
        ASSERT(id < MAX_NUMBER_COMPONENTS, "To many components created.");

        if (!component_mask[id])
        {
            component_mask[id] = true;
            components[id] = new std::vector<T>;
        }

        std::vector<T>* array = (std::vector<T>*)components[id];
        array->emplace_back(std::forward<TemplateArgs>(args)...);

        return &array->back();
    }

    template <typename T>
    inline bool has_component() const noexcept
    {
        unsigned int id = get_component_id<T>();
        return component_mask[id];
    }

    template <typename T>
    std::vector<T>& get_component_array() const
    {
        unsigned int id = get_component_id<T>();
        ASSERT(has_component<T>(), "Component [ID=%i] doesn't exist.", id);
        std::vector<T>* array = (std::vector<T>*)components[id];
        return *array;
    }

    template <typename T, typename... TemplateArgs>
    void update(TemplateArgs&&... args) const
    {
        std::vector<T>& components = get_component_array<T>();       // Without the reference it's getting  a copy.
        for (T& component : components)                              // Without the reference it's updating a copy.
            component.update(std::forward<TemplateArgs>(args)...);
    }

    Entity& create_entity();
    std::vector<Entity> get_entities() const;
};


// FIXME(ted): Class contains a lot of pointers that shouldn't be freed. Figure out relationship to manager.
class Entity
{
private:
    ComponentManager* manager;

    // This is the bone of the Entity.
    std::vector<Component*> components;

    // These are for quick checking and retrieval of components.
    std::array<Component*, MAX_NUMBER_COMPONENTS> component_array{nullptr};
    std::bitset<MAX_NUMBER_COMPONENTS> component_mask{0};

public:
    explicit Entity(ComponentManager* manager) : manager(manager) {};
    ~Entity() = default;  // Everything is cleaned up by the manager.

    template <typename T, typename... TemplateArgs>
    T& add_component(TemplateArgs&&... args)
    {
        unsigned int id = get_component_id<T>();

        if (component_mask[id])          // TODO(ted): Adding an existing component should replace the component.
            ASSERT(false, "Fix this!");  // TODO(ted): Fix this!

        // The pointer should NOT be freed by the entity class. It's freed by the manager.
        Component* component = manager->add_component<T>(*this, std::forward<TemplateArgs>(args)...);

        component_mask[id] = true;
        components.push_back(component);
        component_array[id] = component;

        return *static_cast<T*>(component);
    }

    template <typename T>
    bool has_component() const  // Important! All components acts on const references to entities.
    {
        unsigned int id = get_component_id<T>();
        return component_mask[id];
    }

    template <typename T>
    T& get_component() const  // Important! All components acts on const references to entities.
    {
        unsigned int id = get_component_id<T>();
        ASSERT(has_component<T>(), "Entity doesn't have component [ID=%i].", id);
        return *static_cast<T*>(component_array[id]);  // Will throw error if component isn't publicly inherited.
    }

    void kill() const
    {

    }
};


#endif //OPENGLPROJECT_ENTITY_H
