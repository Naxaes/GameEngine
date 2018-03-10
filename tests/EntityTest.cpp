//
// Created by Ted Klein Bergman on 3/10/18.
//

#include "EntityTest.h"
#if RUN_ENTITY_TEST


#include <iostream>
#include <vector>
#include <array>
#include <bitset>
#include <cassert>



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

class TestComponent : public Component
{
public:
    TestComponent(const Entity& entity, int a, int b, int c) : Component(entity)
    {
        printf("Creating component with values %i, %i, %i.\n", a, b, c);
    }

    void update() override
    {
        printf("Running code...\n");
    }
};


int main()
{
    Entity entity;
    entity.add_component<TestComponent>(1, 2, 3);
    entity.update();

    return 0;
}




#endif