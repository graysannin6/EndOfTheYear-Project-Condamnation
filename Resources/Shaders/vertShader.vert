#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

out vec4 vertexColor; // specify a color output to the fragment shader
out vec3 o_normal;
out vec3 o_pos;
out mat4 ModelMat;
out vec2 TexCoords;

uniform mat4 ModelMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 CameraMatrix;

void main()
{
    //transpose(ProjectionMatrix) * transpose(CameraMatrix)
    TexCoords = aTexCoords;
    gl_Position = ProjectionMatrix * CameraMatrix * ModelMatrix * vec4(aPos, 1.0f);
    vertexColor = vec4(1.0, 1.0, 1.0, 1.0); // set the output variable to a dark-red color
    o_pos = vec3(ModelMatrix * vec4(aPos, 1.0f));
    o_normal = normalize(mat3(ModelMatrix) * aNormal);
    ModelMat = ModelMatrix;
}