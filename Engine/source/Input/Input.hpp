#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include "InputCodes.h"

#include "Maths.hpp"

class Input {
public:
    Input(GLFWwindow* handle);
    ~Input();

	bool IsKeyPressed(int keycode) const;
	bool IsKeyReleased(int keycode) const;

	bool IsMouseButtonPressed(int button) const;
	bool IsMouseButtonReleased(int button) const;

	inline Vec2F GetCursorPos() const { return cursorPos; }
	inline Vec2F GetCursorMove() const { return cursorMove; }
	void Update();

private:
    GLFWwindow* mHandle;
	bool mFirstUpdate = true;
	Vec2F cursorMove;
	Vec2F cursorPos;

};