//
// Created by Ted Klein Bergman on 3/6/18.
//

#include "Entity.h"

#if 0
template <typename T, unsigned int size>
class ComponentArray
{
private:
    T content[size] = {};
    unsigned int last = 0;

public:

    bool add(T component)
    {
        if (last >= size)
            return false;

        content[last++] = component;
        return true;
    }

    void remove(T component)
    {

    }

};




Entity& ComponentManager::create_entity()
{
    entities.emplace_back(this);
    return entities.back();
}


std::vector<Entity> ComponentManager::get_entities() const
{
    return entities;
}



template <unsigned int MAX_COMPONENTS>
class _ComponentManager
{
private:
    std::array<void*, MAX_COMPONENTS> components{nullptr};
    std::bitset<MAX_COMPONENTS> component_mask{0};

    std::vector<Entity> entities;  // Return index in create_entity();

public:

    _ComponentManager() = default;
    ~_ComponentManager()
    {
        for (unsigned int i = 0; i < components.size(); i++)
            if (components[i] != nullptr)
                delete components[i];
    }

    inline unsigned int generate_component_id() const noexcept
    {
        static unsigned int id{0u};
        return id++;
    }

    template <typename T>
    inline unsigned int get_component_id() const noexcept
    {
        static_assert(std::is_base_of<Component, T>(), "Component must be inherited from Component.");
        static unsigned int id{generate_component_id()};
        return id;
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
        std::vector<T> components = get_component_array<T>();
        for (T component : components)
            component.update(std::forward<TemplateArgs>(args)...);
    }

    Entity& create_entity();
    std::vector<Entity> get_entities() const;
};




// FIXME(ted): Class contains a lot of pointers that shouldn't be freed. Figure out relationship to manager.
class _Entity
{
private:
    ComponentManager* manager;

    // This is the bone of the Entity.
    std::vector<Component*> components;

    // These are for quick checking and retrieval of components.
    std::array<Component*, MAX_NUMBER_COMPONENTS> component_array{nullptr};
    std::bitset<MAX_NUMBER_COMPONENTS> component_mask{0};

public:
    explicit _Entity(ComponentManager* manager) : manager(manager) {};
    ~_Entity() = default;  // Everything is cleaned up by the manager.

    template <typename T, typename... TemplateArgs>
    void add_component(TemplateArgs&&... args)
    {
        unsigned int id = get_component_id<T>();

        if (component_mask[id])          // TODO(ted): Adding an existing component should replace the component.
            ASSERT(false, "Fix this!");  // TODO(ted): Fix this!

        // The pointer should NOT be freed by the entity class. It's freed by the manager.
        Component* component = manager->add_component<T>(*this, std::forward<TemplateArgs>(args)...);

        component_mask[id] = true;
        components.push_back(component);
        component_array[id] = component;
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
#endif