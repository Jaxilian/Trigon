

#version 460 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;

uniform mat4 ProjectionMatrix;
uniform mat4 CameraTransform;
uniform mat4 ModelTransform;

void main()
{
    TexCoords = vertexUV;
    WorldPos = vec3(ModelTransform * vec4(vertexPosition_modelspace, 1.0));
    Normal = mat3(ModelTransform) * vertexNormal;   

    mat4 mvp = ProjectionMatrix * CameraTransform * ModelTransform;

    gl_Position =   mvp * vec4(vertexPosition_modelspace,1);
}

