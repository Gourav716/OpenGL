#version 330 core

out vec4 objectColor;

in vec3 color;
in vec2 tex;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D u_texColor;
uniform sampler2D u_texSpecular;
uniform vec3 u_lightColor;
uniform vec3 u_lightPos;
uniform vec3 u_cameraPos;

float ambient = 0.2f;
float specAmount = 0.5f;

vec3 lightVec = u_lightPos - fragPos;
vec3 viewDir = normalize(u_cameraPos - fragPos);

vec4 PointLight()
{
	float a = 3.0f;
	float b = 0.7f;
	
	float lightDist = length(lightVec);
	float intensity = 1 / (a * pow(lightDist, 2) + b * lightDist + 1.0f);

	vec3 lightDir = normalize(lightVec);
	float diffuse = max(dot(lightDir, normal), 0.0f);

	vec3 reflectDir = reflect(-lightDir, normal);
	float specular = pow(max(dot(reflectDir, viewDir), 0.0f), 32.0f) * specAmount;

	//return vec4(color, 1.0f) * vec4(u_lightColor, 1.0f) * (ambient * intensity + diffuse + specular * intensity);
	return (texture(u_texColor, tex) * (ambient * intensity + diffuse) + texture(u_texSpecular, tex).r * (specular * intensity)) * vec4(u_lightColor, 1.0f);
}

vec4 DirectionalLight()
{
	vec3 lightDir = normalize(vec3(0.0f, 1.0f, 1.0f));
	float diffuse = max(dot(lightDir, normal), 0.0f);

	vec3 reflectDir = reflect(-lightDir, normal);
	float specular = pow(max(dot(reflectDir, viewDir), 0.0f), 32.0f) * specAmount;

	//return vec4(color, 1.0f) * vec4(u_lightColor, 1.0f) * (ambient + diffuse + specular);
	return (texture(u_texColor, tex) * (ambient + diffuse) + texture(u_texSpecular, tex).r * specular) * vec4(u_lightColor, 1.0f);
}

vec4 SpotLight()
{
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	vec3 lightDir = normalize(u_lightPos - fragPos);
	float diffuse = max(dot(lightDir, normal), 0.0f);

	vec3 reflectDir = reflect(-lightDir, normal);
	float specular = pow(max(dot(reflectDir, viewDir), 0.0f), 32.0f) * specAmount;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDir);
	float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	//return vec4(color, 1.0f) * vec4(u_lightColor, 1.0f) * (ambient + diffuse + specular);
	return (texture(u_texColor, tex) * (ambient * intensity + diffuse) + texture(u_texSpecular, tex).r * (specular * intensity)) * vec4(u_lightColor, 1.0f);
}

void main()
{
	objectColor = PointLight();
	//objectColor = DirectionalLight();
	//objectColor = SpotLight();
}