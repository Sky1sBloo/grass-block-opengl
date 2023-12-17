#pragma once
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Vector2.hpp"

/**
 * Class for input handling
 */
class Event
{
public:
	/**
	 * Default constructor for window
	 *
	 * @param window Pointer to window for where event is handled
	 */
	Event(GLFWwindow* window);

	/**
	 * Polls window events
	 */
	void PollEvents();

	/**
	 * Checks input key pressed
	 *
	 * @param key Key from GLFW
	 *
	 * @return The param key is pressed
	 */
	bool KeyPressed(int key);

	/**
	 * Gets the mouse position on screen
	 *
	 * @return Mouse position relative to window
	 */
	const JD::Vector2<double>& GetMousePosition() const { return mMousePos; }
	/**
	 * Returns the mouse offset
	 *
	 * @return Vector 2 of mouse offset
	 */
	const JD::Vector2<double>& GetMouseMovement() const { return mMouseOffset; }
private:
	/**
	 * Processes the mouse input 
	 */
	void ProcessMouseInput();
	
	// Window where event will be handled
	GLFWwindow* mWindow;
	
	// Used for mouse movement
	JD::Vector2<double> mMousePos;
	JD::Vector2<double> mMouseOffset;
	JD::Vector2<double> mLastMousePos;
};
