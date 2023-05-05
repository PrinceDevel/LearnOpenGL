#pragma once

#include "Input/Input.hpp"
#include "Logger/Logger.hpp"

#include <memory>
#include <GLFW/glfw3.h>

class Application 
{
public:
    Application(const unsigned int width, const unsigned int height, const char* name);
    Application(const Application& obj) = delete;
    virtual ~Application();

    void Run();
    inline static Application* GetInstance() { return instance; }

protected:
    bool Init();
    virtual void OnRender() = 0;
    virtual void OnInput() = 0;
    virtual void OnStart() = 0;
    
    // Callbacks
    virtual void OnScreenResize() = 0;

protected:
    unsigned int WIDTH, HEIGHT;
    const char* NAME;
    static Application* instance;

    bool initSuccess = false;
    bool cursorEnabled = false;
    int fps = 0;
    float deltaTime = 0.0f;
	
    std::unique_ptr<Input> input;
    GLFWwindow* window;
};

Application* CreateApplication();