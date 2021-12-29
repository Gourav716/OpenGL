#version 330 core

out vec4 objectColor;

in vec3 color;
in vec2 tex;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D u_texture;
uniform vec3 u_lightColor;
uniform vec3 u_lightPos;
uniform vec3 u_cameraPos;

void main()
{
	float ambient = 0.2f;
	float specAmount = 0.5f;
	
	vec3 lightDir = normalize(u_lightPos - fragPos);
	float diffuse = max(dot(lightDir, normal), 0.0f);

	vec3 viewDir = normalize(u_cameraPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float specular = pow(max(dot(reflectDir, viewDir), 0.0f), 32.0f) * specAmount;

	objectColor = vec4(color, 1.0f) * vec4(u_lightColor, 1.0f) * (ambient + diffuse + specular);
	objectColor = texture(u_texture, tex) * vec4(u_lightColor, 1.0f) * (ambient + diffuse + specular);
}