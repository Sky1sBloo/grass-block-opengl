#include <iostream>
#include <cmath>
#include <random>

#include <glad/glad.h>
#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.hpp"
#include "Event.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "VAO.hpp"
#include "BufferObject.hpp"
#include "Texture.hpp"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

int main()
{
	// Setup random number
	std::random_device rd;
	std::mt19937 gen(rd());

	// Load window
	Window::InitializeGLFW();
	Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "Grass Block", {
			{GLFW_RESIZABLE, false}
			});

	window.MakeCurrent();
	window.SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	// Load Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize glad" << std::endl;
		return -1;
	}
	window.BindGladViewport();
	glEnable(GL_DEPTH_TEST);

	// Load texture
	Texture grassTex("textures/grass-tex.jpg", GL_TEXTURE0);	
	
	// Vertex
	GLfloat vertices[] = {
		// Front back
		-1.f, 1.f, 1.f, 0.25f, 1.f / 3.f,  // FTL
		-1.f, -1.f, 1.f, 0.25f, 2.f / 3.f,  // FBL
		1.f, -1.f, 1.f, 0.5f, 2.f / 3.f, // FBR
		1.f, 1.f, 1.f, 0.5f, 1.f / 3.f,  // FTR

		// Sides
		-1.f, 1.f, -1.f, 0.f, 1.f / 3.f, // BTL
		-1.f, -1.f, -1.f, 0.f, 2.f / 3.f,  // BBL
		1.f, 1.f, -1.f, 0.25f, 1.f / 3.f,  // BBR
		1.f, -1.f, -1.f, 0.25f, 2.f / 3.f,   // BTR
		
		// Top
		-1.f, 1.f, 1.f, 0.25f, 0.f,  // TBL
		-1.f, 1.f, -1.f, 0.25f, 1.f / 3.f,  // TFL
		1.f, 1.f, -1.f, 0.5f, 1.f / 3.f,  // TFR
		1.f, 1.f, 1.f, 0.5f, 0.f,  // TBR

		// Bottom
		-1.f, -1.f, 1.f, 0.25f, 2.f / 3.f,  // BBL
		-1.f, -1.f, -1.f, 0.25f, 1.f,  // BFL
		1.f, -1.f, -1.f, 0.5f, 1.f,  // BFR
		1.f, -1.f, 1.f, 0.5f, 2.f / 3.f  // BBR
	}; 

	GLuint indices[] = {
		// Front face
		0, 1, 2,
		0, 3, 2,
		// Left face
		0, 5, 1,
		0, 4, 5,
		// Right face
		3, 7, 6,
		3, 7, 2,
		// Back face
		4, 5, 6,
		5, 6, 7,
		// Top face
		8, 9, 10,
		8, 10, 11,
		// Bottom face
		12, 13, 14,
		12, 14, 15
	};

	// Random boxes
	const GLfloat minDistance = 5.f;
	const GLfloat maxDistance = 20.f;
	std::uniform_real_distribution<float> boxDist(minDistance, maxDistance);

	// Resize vertices except from tex coord
	VAO vao;
	vao.Bind();

	BufferObject vbo(GL_ARRAY_BUFFER);
	vbo.Bind();
	vbo.SetBufferData(sizeof(vertices), vertices, GL_STATIC_DRAW);

	BufferObject ebo(GL_ELEMENT_ARRAY_BUFFER);
	ebo.Bind();
	ebo.SetBufferData(sizeof(indices), indices, GL_STATIC_DRAW);

	vao.DefineArrayAttribute(0, 3, 5, 0);
	vao.DefineArrayAttribute(1, 2, 5, 3);

	vbo.Unbind();
	vao.Unbind();
	ebo.Unbind();

	// Coordinate system
	glm::mat4 model = glm::mat4(1.f);
	glm::mat4 projection = glm::perspective(glm::radians(70.f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.f);

	// Camera
	glm::vec3 cameraPos = glm::vec3(0.f, 0.f, -5.f);
	glm::vec3 cameraFront = glm::vec3(0.f, 0.f, 1.f);
	glm::vec3 cameraUp = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 cameraDirection;
	float cameraSpeed = 3.0f;
	const float cameraSens= 0.1f;
	float pitch, roll, yaw;
	yaw = 90.f;

	// Load shaders
	Shader vertexShader("shaders/3d-perspective.vert", GL_VERTEX_SHADER);
	Shader fragmentShader("shaders/col-shader.frag", GL_FRAGMENT_SHADER);
	ShaderProgram shaderProgram({ vertexShader.GetId(), fragmentShader.GetId() });

	// Window loop
	Event ev(window.GetID());
	float deltaTime = 0.f;
	float prevTime = 0.f;
	while (!window.ShouldClose())
	{
		// Setup deltaTime
		deltaTime = glfwGetTime() - prevTime;
		prevTime = glfwGetTime();
		// Input control
		ev.PollEvents();

		if (ev.KeyPressed(GLFW_KEY_ESCAPE))
			window.Close();

		// Movement
		if (ev.KeyPressed(GLFW_KEY_W))
			cameraPos += glm::normalize(glm::vec3(cameraFront.x, 0, cameraFront.z)) * cameraSpeed * deltaTime;
		if (ev.KeyPressed(GLFW_KEY_S))
			cameraPos -= glm::normalize(glm::vec3(cameraFront.x, 0, cameraFront.z)) * cameraSpeed * deltaTime;
		if (ev.KeyPressed(GLFW_KEY_D))
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
		if (ev.KeyPressed(GLFW_KEY_A))
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
		if (ev.KeyPressed(GLFW_KEY_SPACE))
			cameraPos += glm::vec3(0.f, 1.f, 0.f) * cameraSpeed * deltaTime;
		if (ev.KeyPressed(GLFW_KEY_LEFT_SHIFT))
			cameraPos -= glm::vec3(0.f, 1.f, 0.f) * cameraSpeed * deltaTime;

		// Mouse Movement
		yaw += ev.GetMouseMovement().x * cameraSens;
		pitch += ev.GetMouseMovement().y * cameraSens;

		if (pitch > 89.f)
			pitch = 89.f;
		else if (pitch  < -89.f)
			pitch = -89.f;

		cameraDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraDirection.y = sin(glm::radians(pitch));
		cameraDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	
		cameraFront = glm::normalize(cameraDirection);
		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		// Background color 
		glClearColor(0.1f, 0.5f, 0.5f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw
		grassTex.Bind();
		
		shaderProgram.Use();
		glUniformMatrix4fv(shaderProgram.GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(shaderProgram.GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(shaderProgram.GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniform1i(shaderProgram.GetUniformLocation("texSampler"), 0);
		
		vao.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]) + 1, GL_UNSIGNED_INT, 0);
		vao.Unbind();
	
		window.SwapBuffers();
	}

	Window::TerminateGLFW();

	return 0;
}
