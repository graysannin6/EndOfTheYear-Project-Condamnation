#version 450 core
out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  
in vec3 o_normal;
in vec3 o_pos;

uniform vec3 lightColor;

void main()
{
    FragColor = vec4(lightColor, 1.0);
}
