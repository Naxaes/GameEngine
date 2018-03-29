//
// Created by Ted Klein Bergman on 3/10/18.
//

#include "Shader.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gl_debug.h"
#include "debug.h"


static GLuint current_shader = 0;


enum class ShaderType
{
    NONE     = -1,
    VERTEX   = 0,
    FRAGMENT = 1
};



ShaderSources Shader::load(String filepath)
{
    std::ifstream stream(filepath);

    ASSERT(stream.good(), "Couldn't open file %s.", filepath);

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

GLuint Shader::compile()
{
    const char* vertex_source   = sources.vertex.c_str();
    const char* fragment_source = sources.fragment.c_str();

    // SHADERS
    GLuint vertexID;
    GLCALL(vertexID = glCreateShader(GL_VERTEX_SHADER));
    GLCALL(glShaderSource(vertexID, 1, &vertex_source, nullptr));
    GLCALL(glCompileShader(vertexID));
    check_shader_status(vertexID, GL_COMPILE_STATUS);

    GLuint fragmentID;
    GLCALL(fragmentID = glCreateShader(GL_FRAGMENT_SHADER));
    GLCALL(glShaderSource(fragmentID, 1, &fragment_source, nullptr));
    GLCALL(glCompileShader(fragmentID));
    check_shader_status(fragmentID, GL_COMPILE_STATUS);
    // SHADERS END

    // PROGRAM
    GLuint programID;
    GLCALL(programID = glCreateProgram());

    GLCALL(glAttachShader(programID, vertexID));
    GLCALL(glAttachShader(programID, fragmentID));

    for (unsigned int i = 0; i < attributes.size(); i++)
    {
        GLCALL(glBindAttribLocation(programID, i, attributes[i]));
    }

    GLCALL(glLinkProgram(programID));
    check_program_status(programID, GL_LINK_STATUS);

    GLCALL(glValidateProgram(programID));
    check_program_status(programID, GL_VALIDATE_STATUS);
    // PROGRAM END

    // CLEAR
    GLCALL(glDetachShader(programID, vertexID));
    GLCALL(glDetachShader(programID, fragmentID));
    GLCALL(glDeleteShader(vertexID));
    GLCALL(glDeleteShader(fragmentID));

    return programID;
}


std::unordered_map<const char*, GLint> Shader::cache_locations()
{
    std::unordered_map<const char*, GLint> locations;

    for (const char* uniform : uniforms)
    {
        GLCALL(locations[uniform] = glGetUniformLocation(id, uniform));
    }

    return locations;
}


void Shader::bind() const
{
    current_shader = id;
    GLCALL(glUseProgram(id));
}

void Shader::bind_uniform(const char* location, glm::mat4& matrix, GLboolean normalized) const
{
    ASSERT(current_shader == id, "Shader %i is not bound!", id);
    GLCALL(glUniformMatrix4fv(locations.at(location), 1, normalized, glm::value_ptr(matrix)));
}

void Shader::bind_uniform(const char* location, float v1) const
{
    ASSERT(current_shader == id, "Shader %i is not bound!", id);
    GLCALL(glUniform1f(locations.at(location), v1));
}

void Shader::bind_uniform(const char* location, float v1, float v2) const
{
    ASSERT(current_shader == id, "Shader %i is not bound!", id);
    GLCALL(glUniform2f(locations.at(location), v1, v2));
}

void Shader::bind_uniform(const char* location, float v1, float v2, float v3) const
{
    ASSERT(current_shader == id, "Shader %i is not bound!", id);
    GLCALL(glUniform3f(locations.at(location), v1, v2, v3));
}

void Shader::bind_uniform(const char* location, float v1, float v2, float v3, float v4) const
{
    ASSERT(current_shader == id, "Shader %i is not bound!", id);
    GLCALL(glUniform4f(locations.at(location), v1, v2, v3, v4));
}

void Shader::bind_uniform(const char* location, unsigned int value) const
{
    ASSERT(current_shader == id, "Shader %i is not bound!", id);
    GLCALL(glUniform1ui(locations.at(location), value));
}

void Shader::bind_uniform(const char* location, int value) const
{
    ASSERT(current_shader == id, "Shader %i is not bound!", id);
    GLCALL(glUniform1i(locations.at(location), value));
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