//
// Created by Ted Klein Bergman on 3/6/18.
//

#include "Entity.h"

//#include <vector>
//#include <array>
//#include <bitset>
//#include <cassert>
//
//
//constexpr unsigned int MAX_COMPONENTS = 32;
//
//class Entity;
//class Component;
//
//static unsigned int generate_component_id()
//{
//    static unsigned int id{0u};
//    return id++;
//}
//
//template <typename T> static unsigned int get_component_id()
//{
//    static_assert(std::is_base_of<T, Component>(), "Component must be inherited from Component.");
//    static unsigned int id{generate_component_id()};
//    return id;
//}
//
//
//class Component
//{
//private:
//    const Entity& entity;
//
//public:
//    explicit Component(const Entity& entity) : entity(entity) {}
//    virtual void update() {}
//    virtual ~Component() = default;
//};
//
//
//
//class Entity
//{
//private:
//    std::vector<std::shared_ptr<Component>> components;
//    std::array<std::shared_ptr<Component>, MAX_COMPONENTS> component_array;
//    std::bitset<MAX_COMPONENTS> component_mask;
//
//public:
//
//    explicit Entity() {}
//
//    ~Entity() {}  // Everything is cleaned up by vector with smart pointers.
//
//    template <typename T, typename... TemplateArgs> void add_component(TemplateArgs... args)
//    {
//        unsigned int id = get_component_id<T>();
//
//        T component{new T(*this, std::forward<TemplateArgs>(args)...)};
//
//        component_mask[id] = true;
//        components.emplace_back(component);
//        component_array[id] = std::make_shared<Component>(component);
//    }
//
//    template <typename T> bool has_component() const
//    {
//        unsigned int id = get_component_id<T>();
//        return component_mask[id];
//    }
//
//    template <typename T> T& get_component() const
//    {
//        unsigned int id = get_component_id<T>();
//        assert(has_component<T>());
//        return *component_array[id];
//    }
//
//    void update() const
//    {
//        for (const std::shared_ptr<Component>& component : components)
//            component->update();
//    }
//};