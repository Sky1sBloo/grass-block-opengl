#include "Event.hpp"

Event::Event(GLFWwindow* window) :
	mWindow(window), mMousePos(JD::Vector2<double>(0.0, 0.0)),  
	mMouseOffset(JD::Vector2<double>(0.0, 0.0))
{
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	mLastMousePos = JD::Vector2<double>(
			static_cast<double>(windowWidth) / 2,
			static_cast<double>(windowHeight) / 2
			);
}

void Event::PollEvents()
{
	glfwPollEvents();

	ProcessMouseInput();
}

bool Event::KeyPressed(int key)
{
	return glfwGetKey(mWindow, key) == GLFW_PRESS;
}
	
void Event::ProcessMouseInput()
{
	glfwGetCursorPos(mWindow, &mMousePos.x, &mMousePos.y);

	mMouseOffset.x = mMousePos.x - mLastMousePos.x;
	mMouseOffset.y = mLastMousePos.y - mMousePos.y;
	mLastMousePos.x = mMousePos.x;
	mLastMousePos.y = mMousePos.y;
}
