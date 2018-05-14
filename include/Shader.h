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
};


class Shader
{
private:
    // NOTE(ted): ORDER IMPORTANT! It's the order they're initialized, regardless of the order of the mem-initializers.
    const std::vector<std::string> attributes;
    const std::vector<std::string> uniforms;
    const ShaderSources sources;
    const GLuint id;
    const std::unordered_map<std::string, GLint> locations;

    static std::vector<ShaderInfo> info;

public:
    Shader(const std::string& filepath, std::vector<std::string>& attributes_, std::vector<std::string>& uniforms_)
            : attributes(std::move(attributes_)),
              uniforms(std::move(uniforms_)),
              sources(load(filepath)),
              id(compile(sources, attributes)),
              locations(cache_locations(id, uniforms))
    {}


    void bind() const;
    void bind_uniform(const std::string& location, const glm::mat4& matrix, GLboolean normalized=GL_FALSE) const;
    void bind_uniform(const std::string& location, float v1) const;
    void bind_uniform(const std::string& location, float v1, float v2) const;
    void bind_uniform(const std::string& location, float v1, float v2, float v3) const;
    void bind_uniform(const std::string& location, float v1, float v2, float v3, float v4) const;
    void bind_uniform(const std::string& location, unsigned int value) const;
    void bind_uniform(const std::string& location, int value) const;
    void bind_texture(GLuint id, unsigned int unit = 0) const;


    static ShaderSources load(const std::string& filepath);
    static GLuint compile(const ShaderSources& sources, const std::vector<std::string>& attributes);
    static std::unordered_map<std::string, GLint> cache_locations(GLuint id, const std::vector<std::string>& uniforms);
};


#endif //OPENGLPROJECT_SHADER2_H
