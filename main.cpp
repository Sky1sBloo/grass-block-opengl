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
#include "Primitives.hpp"

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

	// Cube 1
	Cube cube;
	VAO vao;
	vao.Bind();
	BufferObject vbo(GL_ARRAY_BUFFER);
	vbo.Bind();
	vbo.SetBufferData(cube.GetVertices().size() * sizeof(cube.GetVertices()),
			&cube.GetVertices().front(),
			GL_STATIC_DRAW);

	BufferObject ebo(GL_ELEMENT_ARRAY_BUFFER);
	ebo.Bind();
	ebo.SetBufferData(cube.GetIndices().size() * sizeof(cube.GetIndices()),
			&cube.GetIndices().front(),
			GL_STATIC_DRAW);

	vao.DefineArrayAttribute(0, 3, 8, 0);
	vao.DefineArrayAttribute(1, 3, 8, 3);
	vao.DefineArrayAttribute(2, 2, 8, 6);

	vbo.Unbind();
	vao.Unbind();
	ebo.Unbind();

	// Light
	glm::vec3 lightColor = glm::vec3(1.f, 1.f, 0.1f);
	VAO lightVAO;
	lightVAO.Bind();

	vbo.Bind();
	ebo.Bind();

	lightVAO.DefineArrayAttribute(0, 3, 8, 0);

	vbo.Unbind();
	lightVAO.Unbind();
	ebo.Unbind();

	// Coordinate system
	glm::mat4 model = glm::mat4(1.f);
	glm::vec3 lightPos = glm::vec3(3.f, 5.f, 4.f);
	glm::mat4 lightModel = glm::mat4(1.f);
	lightModel = glm::scale(lightModel, glm::vec3(0.5f, 0.5f, 0.5f));
	lightModel = glm::translate(lightModel, lightPos);
	glm::mat4 projection = glm::perspective(glm::radians(70.f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.f);
	float specularStrength = 0.5f;

	// Camera
	glm::vec3 cameraPos = glm::vec3(0.f, 0.f, 5.f);
	glm::vec3 cameraFront = glm::vec3(0.f, 0.f, 1.f);
	glm::vec3 cameraUp = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 cameraDirection;
	float cameraSpeed = 3.0f;
	const float cameraSens= 0.1f;
	float pitch, roll, yaw;
	yaw = -90.f;

	// Load shaders
	Shader vertexShader("shaders/3d-perspective.vert", GL_VERTEX_SHADER);
	Shader fragmentShader("shaders/texture-shader.frag", GL_FRAGMENT_SHADER);
	Shader flatFragmentShader("shaders/col-shader.frag", GL_FRAGMENT_SHADER);
	ShaderProgram shaderProgram({ vertexShader.GetId(), fragmentShader.GetId() });
	ShaderProgram lightShaderProgram({ vertexShader.GetId(),flatFragmentShader.GetId() });

	vertexShader.DeleteShader();
	fragmentShader.DeleteShader();
	flatFragmentShader.DeleteShader();

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


		// Camera logic
		cameraDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraDirection.y = sin(glm::radians(pitch));
		cameraDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	
		cameraFront = glm::normalize(cameraDirection);
		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		// Transform
		float radius = 2.5f;
		lightPos = glm::vec3(5 * cos(glfwGetTime()),
				5 * cos(glfwGetTime()),	
				5 * sin(glfwGetTime()));
				
		lightModel = glm::translate(model, lightPos);

		// Background color 
		glClearColor(0.1f, 0.5f, 0.5f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw
		grassTex.Bind();
		
		// Draw model
		shaderProgram.Use();
		shaderProgram.SetUniformMat4f("model", model);
		shaderProgram.SetUniformMat4f("view", view);
		shaderProgram.SetUniformMat4f("projection", projection);
		shaderProgram.SetUniform1i("texSampeler", 0);
		shaderProgram.SetUniformVec3f("lightColor", lightColor);
		shaderProgram.SetUniformVec3f("lightPos", lightPos);
		shaderProgram.SetUniformVec3f("viewPos", cameraPos);
		
		vao.Bind();
		glDrawElements(GL_TRIANGLES, cube.GetIndices().size(), GL_UNSIGNED_INT, 0);
		vao.Unbind();
		
		// Light model
		lightShaderProgram.Use();
		lightShaderProgram.SetUniformMat4f("model", lightModel);
		lightShaderProgram.SetUniformMat4f("view", view);
		lightShaderProgram.SetUniformMat4f("projection", projection);
		lightShaderProgram.SetUniformVec3f("baseColor", lightColor);
		glUniform3f(lightShaderProgram.GetUniformLocation("baseColor"), lightColor.x, lightColor.y, lightColor.z);

		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, cube.GetIndices().size(), GL_UNSIGNED_INT, 0);
		lightVAO.Unbind();

		window.SwapBuffers();
	}

	Window::TerminateGLFW();

	return 0;
}
