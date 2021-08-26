#version 460 core


in  vec2		UV;

out vec3 color;

uniform sampler2D albedo;

void main()
{

	vec3 ambientLightning = vec3(0.2,0.2,0.2);
	color = texture( albedo, UV ).rgb * ambientLightning ;
}