#version 460 core


layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;


out vec2 UV;

uniform mat4 ModelTransform;
uniform mat4 CameraTransform;
uniform mat4 ProjectionMatrix;

void main()
{
	mat4 mvp = ProjectionMatrix * CameraTransform * ModelTransform;


	gl_Position =  mvp * vec4(vertexPosition_modelspace,1);

	UV = vertexUV;
}

