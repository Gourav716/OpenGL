#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include"Headers/Shader.h"
#include"Headers/VertexArray.h"
#include"Headers/VertexBuffer.h"
#include"Headers/IndexBuffer.h"
#include"Headers/Texture.h"
#include"Headers/Camera.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include<imgui/imgui.h>
#include<imgui/imgui_impl_opengl3.h>
#include<imgui/imgui_impl_glfw.h>

const unsigned int width = 800;
const unsigned int height = 800;

int main()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW." << std::endl;
		return -1;
	}

	/* Attributes for Object */
	float attributes[] =
	{
			//VERTICES				//COLORS			//TEXTURE				//NORMALS
	   -0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,			 0.0f,  0.5f,  1.0f,				//0
		0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		2.0f, 0.0f,			 0.0f,  0.5f,  1.0f,				//1
		0.0f,  0.5f,  0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 2.0f,			 0.0f,  0.5f,  1.0f,				//2
																					
		0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f,			 1.0f,  0.5f,  0.0f,				//3
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,		2.0f, 0.0f,			 1.0f,  0.5f,  0.0f,				//4
		0.0f,  0.5f,  0.0f,		1.0f, 1.0f, 0.0f,		1.0f, 2.0f,			 1.0f,  0.5f,  0.0f,				//5
																					
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 0.0f,			 0.0f,  0.5f, -1.0f,				//6
	   -0.5f, -0.5f, -0.5f,		0.5f, 0.0f, 0.5f,		2.0f, 0.0f,			 0.0f,  0.5f, -1.0f,				//7
		0.0f,  0.5f,  0.0f,		0.5f, 0.5f, 0.0f,		1.0f, 2.0f,			 0.0f,  0.5f, -1.0f,				//8
																					
	   -0.5f, -0.5f, -0.5f,		0.5f, 0.0f, 0.5f,		0.0f, 0.0f,			-1.0f,  0.5f,  0.0f,				//9
	   -0.5f, -0.5f,  0.5f,		0.5f, 0.5f, 0.0f,		2.0f, 0.0f,			-1.0f,  0.5f,  0.0f,				//10
		0.0f,  0.5f,  0.0f,		0.0f, 0.5f, 0.5f,		1.0f, 2.0f,			-1.0f,  0.5f,  0.0f,				//11

	   -0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 0.0f,			 0.0f, -1.0f,  0.0f,				//12
		0.5f, -0.5f,  0.5f,		0.5f, 0.0f, 0.5f,		2.0f, 0.0f,			 0.0f, -1.0f,  0.0f,				//13
		0.5f, -0.5f, -0.5f,		0.5f, 0.5f, 0.0f,		2.0f, 2.0f,			 0.0f, -1.0f,  0.0f,				//14
	   -0.5f, -0.5f, -0.5f,		0.0f, 0.5f, 0.5f,		0.0f, 2.0f,			 0.0f, -1.0f,  0.0f					//15
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,

		//Bottom Face
		12, 13, 14,
		14, 15, 12
	};

	/* Attributes for Light */
	float lightVertices[] =
	{
		-0.1f, -0.1f,  0.1f,		//0
		 0.1f, -0.1f,  0.1f,		//1
		 0.1f,  0.1f,  0.1f,		//2
		-0.1f,  0.1f,  0.1f,		//3

		-0.1f, -0.1f, -0.1f,		//4
		 0.1f, -0.1f, -0.1f,		//5
		 0.1f,  0.1f, -0.1f,		//6
		-0.1f,  0.1f, -0.1f			//7
	};

	unsigned int lightIndices[] =
	{
		0, 1, 2,
		2, 3, 0,

		1, 5, 6,
		6, 2, 1,

		5, 4, 7,
		7, 6, 5,

		4, 0, 3,
		3, 7, 4,

		3, 2, 6,
		6, 7, 3,

		0, 1, 5,
		5, 4, 0
	};

	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create window." << std::endl;;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	/* Object Creation */
	VertexArray va;
	VertexBuffer vb(sizeof(attributes), attributes);
	IndexBuffer ib(sizeof(indices), indices);
	Shader shader("Shaders/Vertex.vert", "Shaders/Fragment.frag");
	Texture tex("Resources/Chainmail_Color.png");

	va.LinkAttribute(0, 3, 11 * sizeof(float), (void*)0);
	va.LinkAttribute(1, 3, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	va.LinkAttribute(2, 2, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	va.LinkAttribute(3, 3, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	va.UnBind();
	vb.UnBind();
	ib.UnBind();
	tex.UnBind();

	/* Light Creation */
	VertexArray vaLight;
	VertexBuffer vbLight(sizeof(lightVertices), lightVertices);
	IndexBuffer ibLight(sizeof(lightIndices), lightIndices);
	Shader shaderLight("Shaders/LightVertex.vert", "Shaders/LightFragment.frag");

	vaLight.LinkAttribute(0, 3, 3 * sizeof(float), (void*)0);

	vaLight.UnBind();
	vbLight.UnBind();
	ibLight.UnBind();

	/* Initialize ImGui */
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& IO = ImGui::GetIO();
	IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	ImGui_ImplOpenGL3_Init();
	ImGui_ImplGlfw_InitForOpenGL(window, false);

	glEnable(GL_DEPTH_TEST);

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
	glm::vec3 clearColor = glm::vec3(0.2f, 0.19f, 0.21f);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);

	Camera camera(width, height, cameraPos);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/* ImGui Window */
		ImGui::Begin("ImGui");

		ImGui::ColorEdit3("BackGround Color", &clearColor.x);
		ImGui::ColorEdit3("Light Color", &lightColor.x);
		ImGui::SliderFloat3("Light Position", &lightPos.x, -1.0f, 1.0f, "%.1f");

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Object Rendering */
		shader.Activate();
		va.Bind();
		tex.Bind();
		shader.SetUniform1i("u_texture", 0);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		camera.Movement(window);
		glm::mat4 MVP = camera.MVPMatrix(60.0f) * model;
		shader.SetUniformMat4f("u_MVP", MVP);
		shader.SetUniformMat4f("u_model", model);
		shader.SetUniform3f("u_lightColor", lightColor.x, lightColor.y, lightColor.z);
		shader.SetUniform3f("u_lightPos", lightPos.x, lightPos.y, lightPos.z);
		shader.SetUniform3f("u_cameraPos", cameraPos.x, cameraPos.y, cameraPos.z);

		glad_glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, NULL);

		/* Light Rendering */
		shaderLight.Activate();
		vaLight.Bind();

		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);

		glm::mat4 lightMVP = camera.MVPMatrix(60.0f) * lightModel;
		shaderLight.SetUniformMat4f("u_lightMVP", lightMVP);
		shaderLight.SetUniform3f("u_lightColor", lightColor.x, lightColor.y, lightColor.z);

		glad_glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(unsigned int), GL_UNSIGNED_INT, NULL);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}