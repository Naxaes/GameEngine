//
// Created by Ted Klein Bergman on 3/10/18.
//

#include "EntityTest.h"
#if RUN_ENTITY_TEST

#include "../src/Entity.h"


class SimpleComponent : public Component
{
public:
    int id;

    SimpleComponent(const Entity& entity, int id) : Component(entity), id(id)
    {
        printf("Creating SimpleComponent %i\n", id);
    }

    void update(const char* text, float x)
    {
        printf("Running SimpleComponent %i code: %s, %f\n", id, text, x);
    }
};


class TimeComponent : public Component
{
public:
    int id;
    float time;

    TimeComponent(const Entity& entity, int id) : Component(entity), id(id)
    {
        time = 0;
        printf("Creating TimeComponent %i\n", id);
    }

    void update(float dt)
    {
        time += dt;
        printf("Running TimeComponent %i code: %f, %f\n", id, dt, time);
    }
};


class ParameterTestComponent : public Component
{
public:
    int id;

    ParameterTestComponent(const Entity& entity, int id) : Component(entity), id(id)
    {
        printf("Creating ParameterTestComponent %i\n", id);
    }

    void update(const int* pointer, Entity& reference, bool optional = true)
    {
        if (optional)
            printf("Running ParameterTestComponent %i code: %i, %i\n", id, *pointer, reference.has_component<SimpleComponent>());
        else
            printf("Running ParameterTestComponent %i code: With optional parameter.\n", id);
    }
};

class KillComponent : public Component
{
public:
    int id;
    const Entity& entity;
    TimeComponent& test;

    KillComponent(const Entity& entity, int id) :
            Component(entity), id(id), entity(entity), test(entity.get_component<TimeComponent>())
    {
        printf("Creating KillComponent %i\n", id);

    }

    void update()
    {
        printf("Running KillComponent %i code: ...\n", id);
        if (test.id == 2)
        {
            entity.kill();
            printf("KillComponent %i killed an entity!\n", id);
        }

    }
};


int main()
{
    unsigned int id;
    ComponentManager manager;

    id = 0;
    Entity entity1 = manager.create_entity();
    entity1.add_component<SimpleComponent>(id);
    entity1.add_component<TimeComponent>(id);

    id = 1;
    Entity entity2 = manager.create_entity();
    entity2.add_component<SimpleComponent>(id);
    entity2.add_component<TimeComponent>(id);
    entity2.add_component<KillComponent>(id);

    id = 2;
    Entity entity3 = manager.create_entity();
    entity3.add_component<SimpleComponent>(id);
    entity3.add_component<TimeComponent>(id);
    entity3.add_component<ParameterTestComponent>(id);
    entity3.add_component<KillComponent>(id);


    int x = 10;

    for (unsigned int i = 0; i < 3; i++)
    {
        manager.update<SimpleComponent>("Hello", 1.314f);
        manager.update<TimeComponent>(1.55f);
        manager.update<KillComponent>();
        if (i % 2 == 0)
            manager.update<ParameterTestComponent>(&x, entity1);
        else
            manager.update<ParameterTestComponent>(&x, entity1, false);
    }


    return 0;
}




#endif