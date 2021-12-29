#version 330 core

layout (location = 0) in vec3 vPos;

uniform mat4 u_lightMVP;

void main()
{
	gl_Position = u_lightMVP * vec4(vPos, 1.0f);
}