#include "precompiled.hpp"

#include "Input.hpp"
#include <glad/glad.h>


Input::Input(GLFWwindow* handle) : mHandle(handle), cursorMove(vec2_zero), cursorPos(vec2_zero) {}
Input::~Input() {}

bool Input::IsKeyPressed(int keycode) const 
{
    int state = glfwGetKey(mHandle, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;;
}
bool Input::IsKeyReleased(int keycode) const {
    int state = glfwGetKey(mHandle, keycode);
    return state == GLFW_RELEASE;
}

bool Input::IsMouseButtonPressed(int button) const {
	int state = glfwGetMouseButton(mHandle, button);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}
bool Input::IsMouseButtonReleased(int button) const {
	int state = glfwGetMouseButton(mHandle, button);
	return state == GLFW_RELEASE;
}

void Input::Update() {
	double xPos, yPos;
	glfwGetCursorPos(mHandle, &xPos, &yPos);	
	Vec2F cursorPosN = Vec2F((float)xPos, (float)yPos);
	
	if (mFirstUpdate) {
		cursorPos = cursorPosN;
		mFirstUpdate = false;
	}

	cursorMove = Vec2F( cursorPosN.x - cursorPos.x, cursorPos.y - cursorPosN.y );
	cursorPos = cursorPosN;
}