//
// Created by Ted Klein Bergman on 3/28/18.
//

#ifndef OPENGLPROJECT_COMPONENT_GRAPHICS_H
#define OPENGLPROJECT_COMPONENT_GRAPHICS_H


#include <glad/glad.h>
#include <glm/gtx/transform.hpp>

#include "component.h"
#include "vertex_array_buffer.h"
#include "shader.h"
#include "component_displacement.h"


class GraphicComponent : public Component
{
public:

    VertexArray vao;
    GLuint texture, vertex_count;
    Shader program;
    DisplacementComponent& displacement;

    GraphicComponent(Entity* entity, VertexArray vao, GLuint texture, GLuint vertex_count, const Shader& program) :
            Component(entity), vao(vao), texture(texture), vertex_count(vertex_count), program(program),
            displacement(entity->get_component<DisplacementComponent>())
    {}
    ~GraphicComponent() = default;

    void update(float dt) override {};

    void update()
    {
        glm::mat4 identity = glm::mat4(1.0f);
        glm::mat4 scaled   = glm::scale(displacement.scale);
        glm::mat4 rotatedX = glm::rotate(identity, glm::radians(displacement.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rotatedY = glm::rotate(identity, glm::radians(displacement.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rotatedZ = glm::rotate(identity, glm::radians(displacement.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 translated = glm::translate(identity, displacement.location);

        glm::mat4 transformation_matrix = translated * rotatedX * rotatedY * rotatedZ * scaled;

        program.bind_uniform("transformation", transformation_matrix);

        vao.bind();
        GLCALL(glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, nullptr));
    }
};



#endif //OPENGLPROJECT_COMPONENT_GRAPHICS_H
