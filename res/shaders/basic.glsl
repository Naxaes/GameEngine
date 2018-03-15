#shader vertex
#version 330 core

in vec3 position;

out vec3 pass_position;

uniform mat4 transformation;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    pass_position = position;
    gl_Position = projection * view * transformation * vec4(position, 1.0);
}


#shader fragment
#version 330 core

in vec3 pass_position;

out vec4 color;

uniform float time;

void main()
{
    color = vec4(pass_position * sin(time), 1.0f);
}
