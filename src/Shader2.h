//
// Created by Ted Klein Bergman on 3/10/18.
//

#ifndef OPENGLPROJECT_SHADER2_H
#define OPENGLPROJECT_SHADER2_H


#define check_shader_status(shaderID, status) _check_shader_status(shaderID, status, #status)
#define check_program_status(programID, status) _check_program_status(programID, status, #status)

#include <string>
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

class Shader
{
private:
    void load(const char* filepath);
    void compile();
public:
    GLuint id;
    const std::vector<std::string> attributes;
    const std::vector<std::string> uniforms;
    ShaderSources sources;

    std::unordered_map<std::string, GLint> locations;

    Shader(const std::string& filepath, std::vector<std::string> attributes, std::vector<std::string> uniforms);

    void bind();
    void bind_uniform(const char* location, glm::mat4& matrix, GLboolean normalized=GL_FALSE);
};


#endif //OPENGLPROJECT_SHADER2_H
