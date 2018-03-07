#shader vertex
#version 330 core

in vec3 position;

uniform mat4 transformation;

void main()
{
    gl_Position = transformation * vec4(position, 1.0);
}


#shader fragment
#version 330 core

out vec4 color;

void main()
{
    color = vec4(1.0, 1.0, 1.0, 1.0);
}
