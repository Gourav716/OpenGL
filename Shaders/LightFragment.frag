#version 330 core

out vec4 lightColor;

uniform vec3 u_lightColor;

void main()
{
	lightColor = vec4(u_lightColor, 1.0f);
}