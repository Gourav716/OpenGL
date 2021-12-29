#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

out vec3 color;
out vec2 tex;
out vec3 normal;
out vec3 fragPos;

uniform mat4 u_MVP;
uniform mat4 u_model;

void main()
{
	gl_Position = u_MVP * vec4(aPos, 1.0f);
	fragPos = vec3(u_model * vec4(aPos, 1.0f));
	color = aColor;
	tex = aTex;
	normal = normalize(aNormal);
}