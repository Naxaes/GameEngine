//
// Created by Ted Klein Bergman on 3/10/18.
//

#ifndef OPENGLPROJECT_SHADER2_H
#define OPENGLPROJECT_SHADER2_H


#define check_shader_status(shaderID, status) _check_shader_status(shaderID, status, #status)
#define check_program_status(programID, status) _check_program_status(programID, status, #status)

#include <string>
#include <utility>
#include <vector>
#include <unordered_map>

#include <glad/glad.h>
#include <glm/glm.hpp>

enum class ShaderType;
bool _check_shader_status(GLuint shaderID, GLuint status, const char* status_name);
bool _check_program_status(GLuint programID, GLuint status, const char* status_name);


struct ShaderSources
{
    std::string vertex;
    std::string fragment;
};


struct ShaderInfo
{
    std::vector<const char*> attributes;
    std::vector<const char*> uniforms;

    ShaderSources sources;

    bool is_compiled;
};


class Shader
{
private:
    using String = const char*;
    using StringVector = std::vector<String>;
    using LocationMap  = std::unordered_map<String, GLint>;

    // NOTE(ted): ORDER IMPORTANT! It's the order they're initialized, regardless of the order of the mem-initializers.
    const StringVector  attributes;
    const StringVector  uniforms;
    const ShaderSources sources;
    const GLuint id;
    const LocationMap   locations;

    ShaderSources load(const char* filepath);
    GLuint compile();
    LocationMap cache_locations();

public:

    Shader(String filepath, StringVector attributes, StringVector uniforms)
            : attributes(std::move(attributes)),
              uniforms(std::move(uniforms)),
              sources(load(filepath)),
              id(compile()),
              locations(cache_locations())
    {}


    void bind() const;
    void bind_uniform(String location, glm::mat4& matrix, GLboolean normalized=GL_FALSE) const;
    void bind_uniform(String location, float v1) const;
    void bind_uniform(String location, float v1, float v2) const;
    void bind_uniform(String location, float v1, float v2, float v3) const;
    void bind_uniform(String location, float v1, float v2, float v3, float v4) const;
    void bind_uniform(String location, unsigned int value) const;
    void bind_uniform(String location, int value) const;
    void bind_texture(GLuint id, unsigned int unit = 0) const;
};


#endif //OPENGLPROJECT_SHADER2_H
