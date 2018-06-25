//
// Created by Ted Klein Bergman on 3/10/18.
//

#include "shader.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gl_debug.h"
#include "debug.h"


static GLuint current_shader = 0;

struct ShaderInfo
{
    std::vector<const char*> attributes;
    std::vector<const char*> uniforms;
    ShaderSources sources;
};


enum class ShaderType
{
    NONE     = -1,
    VERTEX   = 0,
    FRAGMENT = 1
};



ShaderSources Shader::load(const std::string& filepath)
{
    std::ifstream stream(filepath);

    ASSERT(stream.good(), "Couldn't open file %s.", filepath.c_str());

    ShaderType type = ShaderType::NONE;
    std::stringstream shader_sources[2];
    std::string line;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
            else
            {
                std::cerr << "Couldn't parse shader." << std::endl;
                exit(-1);
            }
        }
        else
            shader_sources[(int)type] << line << std::endl;
    }

    return {shader_sources[0].str(), shader_sources[1].str()};
}

GLuint create_shader(const char*& vertex_source, GLenum type)
{
    GLuint vertexID;
    GLCALL(vertexID = glCreateShader(type));
    GLCALL(glShaderSource(vertexID, 1, &vertex_source, nullptr));
    GLCALL(glCompileShader(vertexID));
    check_shader_status(vertexID, GL_COMPILE_STATUS);
    return vertexID;
}

GLuint create_program(const std::vector<std::string>& attributes, GLuint vertexID, GLuint fragmentID)
{
    GLuint programID;
    GLCALL(programID = glCreateProgram());

    GLCALL(glAttachShader(programID, vertexID));
    GLCALL(glAttachShader(programID, fragmentID));

    for (unsigned int i = 0; i < attributes.size(); i++)
    {
        GLCALL(glBindAttribLocation(programID, i, attributes[i].c_str()));
    }

    GLCALL(glLinkProgram(programID));
    check_program_status(programID, GL_LINK_STATUS);

    GLCALL(glValidateProgram(programID));
    check_program_status(programID, GL_VALIDATE_STATUS);
    return programID;
}


void clear(GLuint vertexID, GLuint fragmentID, GLuint programID)
{
    GLCALL(glDetachShader(programID, vertexID));
    GLCALL(glDetachShader(programID, fragmentID));
    GLCALL(glDeleteShader(vertexID));
    GLCALL(glDeleteShader(fragmentID));
}


GLuint Shader::compile(const ShaderSources& sources, const std::vector<std::string>& attributes)
{
    const char* vertex_source   = sources.vertex.c_str();
    const char* fragment_source = sources.fragment.c_str();

    GLuint vertexID = create_shader(vertex_source, GL_VERTEX_SHADER);
    GLuint fragmentID = create_shader(fragment_source, GL_FRAGMENT_SHADER);
    GLuint programID = create_program(attributes, vertexID, fragmentID);
    clear(vertexID, fragmentID, programID);

    return programID;
}


std::unordered_map<std::string, GLint> Shader::cache_locations(GLuint id, const std::vector<std::string>& uniforms)
{
    std::unordered_map<std::string, GLint> locations;

    for (const std::string& uniform : uniforms)
    {
        GLCALL(locations[uniform] = glGetUniformLocation(id, uniform.c_str()));
    }

    return locations;
}


void Shader::bind() const
{
    current_shader = id;
    GLCALL(glUseProgram(id));
}

void Shader::bind_uniform(const std::string& location, const glm::mat4& matrix, GLboolean normalized) const
{
    ASSERT(current_shader == id, "Shader %i is not bound!", id);

    GLint index;
    try { index = locations.at(location); }
    catch (const std::out_of_range&) { std::printf("Shader has no uniform %s.", location.c_str()); std::exit(-1); }

    GLCALL(glUniformMatrix4fv(index, 1, normalized, glm::value_ptr(matrix)));
}

void Shader::bind_uniform(const std::string& location, float v1) const
{
    ASSERT(current_shader == id, "Shader %i is not bound!", id);

    GLint index;
    try { index = locations.at(location); }
    catch (const std::out_of_range&) { std::printf("Shader has no uniform %s.", location.c_str()); std::exit(-1); }

    GLCALL(glUniform1f(index, v1));
}

void Shader::bind_uniform(const std::string& location, float v1, float v2) const
{
    ASSERT(current_shader == id, "Shader %i is not bound!", id);

    GLint index;
    try { index = locations.at(location); }
    catch (const std::out_of_range&) { std::printf("Shader has no uniform %s.", location.c_str()); std::exit(-1); }

    GLCALL(glUniform2f(index, v1, v2));
}

void Shader::bind_uniform(const std::string& location, float v1, float v2, float v3) const
{
    ASSERT(current_shader == id, "Shader %i is not bound!", id);

    GLint index;
    try { index = locations.at(location); }
    catch (const std::out_of_range&) { std::printf("Shader has no uniform %s.", location.c_str()); std::exit(-1); }

    GLCALL(glUniform3f(index, v1, v2, v3));
}

void Shader::bind_uniform(const std::string& location, float v1, float v2, float v3, float v4) const
{
    ASSERT(current_shader == id, "Shader %i is not bound!", id);

    GLint index;
    try { index = locations.at(location); }
    catch (const std::out_of_range&) { std::printf("Shader has no uniform %s.", location.c_str()); std::exit(-1); }

    GLCALL(glUniform4f(index, v1, v2, v3, v4));
}

void Shader::bind_uniform(const std::string& location, unsigned int value) const
{
    ASSERT(current_shader == id, "Shader %i is not bound!", id);

    GLint index;
    try { index = locations.at(location); }
    catch (const std::out_of_range&) { std::printf("Shader has no uniform %s.", location.c_str()); std::exit(-1); }

    GLCALL(glUniform1ui(index, value));
}

void Shader::bind_uniform(const std::string& location, int value) const
{
    ASSERT(current_shader == id, "Shader %i is not bound!", id);

    GLint index;
    try { index = locations.at(location); }
    catch (const std::out_of_range&) { std::printf("Shader has no uniform %s.", location.c_str()); std::exit(-1); }

    GLCALL(glUniform1i(index, value));
}

void Shader::bind_texture(GLuint texture_id, unsigned int unit) const
{
    ASSERT(current_shader == id, "Shader %i is not bound!", id);
    GLCALL(glActiveTexture(GL_TEXTURE0 + unit));
    GLCALL(glBindTexture(GL_TEXTURE_2D, texture_id));
}















bool _check_shader_status(GLuint shaderID, GLuint status, const char* status_name)
{
    int success = 0;

    GLCALL(GLCALL(glGetShaderiv(shaderID, status, &success)));

    if (!success)
    {
        int log_size;

        GLCALL(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &log_size));

        char log[log_size];

        GLCALL(glGetShaderInfoLog(shaderID, log_size, nullptr, log));

        std::string formatted_log;

        formatted_log.push_back('\t');
        for (const char character : log)
        {
            formatted_log.push_back(character);
            if (character == '\n') {
                formatted_log.push_back('\t');
            }
        }

        fprintf(
                stderr,
                "[Shader Error] (ID %i, %s):\n%s\n",
                shaderID, status_name, formatted_log.c_str()
        );

        return false;
    }

    return true;
}


bool _check_program_status(GLuint programID, GLuint status, const char* status_name)
{
    int success = 0;

    GLCALL(glGetProgramiv(programID, status, &success));

    if (!success) {
        int log_size;

        GLCALL(glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &log_size));

        char log[log_size];

        GLCALL(glGetProgramInfoLog(programID, log_size, nullptr, log));

        std::string formatted_log;

        formatted_log.push_back('\t');
        for (const char character : log) {
            formatted_log.push_back(character);
            if (character == '\n') {
                formatted_log.push_back('\t');
            }
        }

        fprintf(
                stderr,
                "[Shader Program Error] (ID %i, %s):\n%s\n",
                programID, status_name, formatted_log.c_str()
        );

        return false;
    }

    return true;
}