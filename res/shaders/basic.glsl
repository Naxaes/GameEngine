#shader vertex
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture_coordinates;
layout (location = 2) in vec3 normals;

out vec3 pass_position;
out vec2 pass_texture_coordinate;
out vec3 pass_normal;

uniform mat4 transformation;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    mat4 MVP = projection * view * transformation;
    mat3 MVP_Normal = mat3(transpose(inverse(transformation)));  // https://learnopengl.com/Lighting/Basic-Lighting

    pass_texture_coordinate = texture_coordinates;
    pass_position = vec3(MVP * vec4(position, 1.0));
    pass_normal = normalize(vec3(MVP_Normal * normals));

    gl_Position = MVP * vec4(position, 1.0);
}


#shader fragment
#version 330 core


#define ASSERT(condition, r, g, b) { if (condition) { color = vec3(r, g, b); return; } }

in vec3 pass_position;
in vec2 pass_texture_coordinate;
in vec3 pass_normal;

out vec3 color;

uniform vec3 camera_position;

uniform sampler2D diffuse;
uniform sampler2D specular;
uniform sampler2D emission;

uniform float ambient;
uniform float time;
uniform float shininess;

uniform vec3  light_position;
uniform float light_linear;
uniform float light_quadratic;


bool is_normalized(vec3 a)
{
    bool result = abs(length(a) - 1.0f) < 0.01f;
    return result;
}

float positive_dot(vec3 a, vec3 b)
{
    return max(dot(a, b), 0.0);
}

vec3 rgb_of(sampler2D sampler)
{
    return vec3(texture(sampler, pass_texture_coordinate));
}

vec4 rgba_of(sampler2D sampler)
{
    return texture(sampler, pass_texture_coordinate);
}

float sum(vec3 a)
{
    return a.x + a.y + a.z;
}

void main()
{
    ASSERT(!is_normalized(pass_normal), 1.0f, 0, 0);

    vec3  vector_to_light      = light_position  - pass_position;
    vec3  vector_to_camera     = camera_position - pass_position;
    vec3  direction_to_light   = normalize(vector_to_light);
    vec3  direction_to_camera  = normalize(vector_to_camera);
    vec3  reflection_direction = reflect(-direction_to_light, pass_normal);

    // Attenuation
    float distance = length(vector_to_light);
    float attenuation = 1.0 / (1.0 + light_linear * distance + light_quadratic * distance * distance);

    // Ambient
    float ambient_factor = ambient;
    vec3  ambient_color  = ambient_factor * rgb_of(diffuse);

    // Diffuse
    float diffuse_factor = positive_dot(direction_to_light, pass_normal);
    vec3  diffuse_color  = diffuse_factor * rgb_of(diffuse);

    // Specular
    float specular_factor = pow(positive_dot(direction_to_camera, reflection_direction), shininess);
    vec3  specular_color  = specular_factor * rgb_of(specular);

    // Emission
    float emission_factor = sum(rgb_of(specular)) == 0.0f ? 1.0f : 0.0f;
    vec3  emission_color  = emission_factor * rgb_of(emission) * (sin(time) + 1.0f) / 2.0f;

    color = (ambient_color + diffuse_color + specular_color + emission_color) * attenuation;
}

// Attenuation graph: https://www.desmos.com/calculator/nmnaud1hrw