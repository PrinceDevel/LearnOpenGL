#pragma once

#include "Util/Input/Input.hpp"
#include "Util/Logger/Logger.hpp"

#include <memory>
#include <GLFW/glfw3.h>

class Application 
{
public:
    Application(const unsigned int width, const unsigned int height, const char* name);
    virtual ~Application();

    void Run();

protected:
    bool Init();
    virtual void OnRender() = 0;
    virtual void OnInput() = 0;
    virtual void OnStart() = 0;

protected:
    const unsigned int WIDTH, HEIGHT;
    const char* NAME;

    bool initSuccess = false;
    bool cursorEnabled = false;
    int fps = 0;
    float deltaTime = 0.0f;
	
    std::unique_ptr<Input> input;
    GLFWwindow* window;
};

Application* CreateApplication();