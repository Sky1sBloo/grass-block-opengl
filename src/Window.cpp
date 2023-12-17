#include "Window.hpp"
#include <iostream>


void Window::InitializeGLFW()
{
	glfwInit();
}


void Window::TerminateGLFW()
{
	glfwTerminate();
}

// For autosizing of Glad viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const std::string& title, const std::map<int, int>& windowHints)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	for (const auto& hint :windowHints)
	{
		glfwWindowHint(hint.first, hint.second);
	}

	mID = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (mID == nullptr)
	{
		std::cerr << "Failed to create window" << std::endl;
		return;
	}

	glfwSetFramebufferSizeCallback(mID, framebuffer_size_callback);	
}

Window::Window(GLFWwindow* window)
{
	mID = window;
}

void Window::MakeCurrent()
{
	glfwMakeContextCurrent(mID);
}

void Window::BindGladViewport()
{
	glfwSetFramebufferSizeCallback(mID, framebuffer_size_callback);
}

void Window::SetInputMode(int mode, int value)
{
	glfwSetInputMode(mID, mode, value);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(mID);
}
