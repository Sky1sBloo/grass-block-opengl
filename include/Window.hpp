#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <map>

/**
 * Wrapper class for GLFW window
 */
class Window
{
public:
	/**
	 * Initializes window with default values
	 */
	static void InitializeGLFW();
	
	/**
	 * Termiantes GLFW
	 */
	static void TerminateGLFW();

	/**
	 * Constructor for window class
	 * ex. 
	 * Window(1024, 768, "Window Title", {{ GLFW_CURSOR, true }, { GLFW_VISIBLE, false }});
	 *
	 * @param width Length of screen
	 * @param height Height of screen
	 * @param title Title of window
	 * @param windowHint map of window hints of current window(TAKE NOTE THAT GLFW_OPENGL_PROFILE AND CONTEXT_VERSION ARE ALREADY SETTED IN CPP FILE)
	 */
	Window(int width, int height, const std::string& title, const std::map<int, int>& windowHints = {});

	/**
	 * Constructor that intiializes a window class based on GLFW window
	 *
	 * @param window GLFW window to be copied
	 */
	Window(GLFWwindow* window);

	/**
	 * Makes the window context current 
	 */
	void MakeCurrent();

	/**
	 * Binds the glad viewport size to your window
	 * Ensure that you load glad before calling this function 
	 */
	void BindGladViewport();
	/**
	 * Checks if the window should close
	 */
	bool ShouldClose() const { return glfwWindowShouldClose(mID); }

	/**
	 * Sets the close flag of the window to true
	 */
	void Close() { glfwSetWindowShouldClose(mID, true); }

	/**
	 * Sets the input option of window
	 * Wrapper function for glfwSetInputMode
	 *
	 * @param mode Setting of input
	 * @param value Value of setting
	 */
	void SetInputMode(int mode, int value);

	/**
	 * Swap window front and back buffers
	 */
	void SwapBuffers();

	/**
	 * Getter for GLFWwindow
	 */
	GLFWwindow* GetID() const { return mID; }
private:
	/**
	 * ID of window
	 */
	GLFWwindow* mID;
};
