#include"Headers/Camera.h"
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/vector_angle.hpp>
#include<imgui/imgui.h>

Camera::Camera(const unsigned int& width, const unsigned int& height, glm::vec3 position)
{
	m_Width = width;
	m_Height = height;
	m_Position = position;
}

glm::mat4 Camera::MVPMatrix(float FOVDeg)
{
	glm::mat4 project = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	project = glm::perspective(glm::radians(FOVDeg), float(m_Width / m_Height), 0.1f, 100.0f);
	view = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);

	return project * view;
}

void Camera::Movement(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		m_Position += speed * glm::normalize(m_Orientation);
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		m_Position += speed * -glm::normalize(m_Orientation);
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		m_Position += speed * glm::normalize(glm::cross(m_Up, m_Orientation));
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		m_Position += speed * -glm::normalize(glm::cross(m_Up, m_Orientation));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE))
	{
		m_Position += speed * glm::normalize(m_Up);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
	{
		m_Position += speed * -glm::normalize(m_Up);
	}

	if (!ImGui::GetIO().WantCaptureMouse)
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			if (firstClick)
			{
				glfwSetCursorPos(window, double(m_Width / 2), double(m_Height / 2));
				firstClick = false;
			}

			double mouseX, mouseY;

			glfwGetCursorPos(window, &mouseX, &mouseY);

			float rotX = sensitivity * float(mouseY - double(m_Width / 2));
			float rotY = sensitivity * float(mouseX - double(m_Height / 2));

			glm::vec3 new_Orientation = glm::rotate(m_Orientation, glm::radians(-rotX), glm::normalize(glm::cross(m_Orientation, m_Up)));

			m_Orientation = new_Orientation;

			m_Orientation = glm::rotate(m_Orientation, glm::radians(-rotY), glm::normalize(m_Up));

			glfwSetCursorPos(window, double(m_Width / 2), double(m_Height / 2));
		}
		else if (!glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			firstClick = true;
		}
	}
}
