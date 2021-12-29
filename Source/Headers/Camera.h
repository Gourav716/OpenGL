#ifndef CAMERA_CLASS
#define CAMERA_CLASS

#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

class Camera
{
public:
	Camera(const unsigned int& width, const unsigned int& height, glm::vec3 position);

	glm::mat4 MVPMatrix(float FOVDeg);
	void Movement(GLFWwindow* window);

private:
	unsigned int m_Width;
	unsigned int m_Height;

	glm::vec3 m_Position = glm::vec3(0.0f);
	glm::vec3 m_Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

	bool firstClick = true;
	const float speed = 0.1f;
	const float sensitivity = 0.1f;
};
#endif // !CAMERA_CLASS
