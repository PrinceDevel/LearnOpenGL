#include "precompiled.hpp"
#include "Application.hpp"


#include <glad/glad.h>

Application* Application::instance = nullptr;

Application::Application(const unsigned int width, const unsigned int height, const char* name) 
: WIDTH(width), HEIGHT(height), NAME(name)
{
	if (instance) delete instance;
	instance = this;
	RB_CORE_DEBUG("Instanciated !!", NULL);

    initSuccess = Init();
}
Application::~Application() 
{
    glfwTerminate();
}

bool Application::Init() 
{
    //------ Initialising GLFW ---------
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //------ Creating Window ---------
	window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		RB_CORE_ERROR("Failed to create GLFW window", NULL);
		glfwTerminate();
		return 0;
	}
	glfwMakeContextCurrent(window);

    //------ Initialising Glad ---------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
        RB_CORE_ERROR("Failed to initialize GLAD", NULL);
        glfwTerminate();
        return 0;
	}
	glViewport(0, 0, WIDTH, HEIGHT);

    //------ Printing Info ---------
	RB_CORE_INFO("--- OpenGL Info ---", NULL);
	RB_CORE_INFO("Vendor: %s", glGetString(GL_VENDOR));
	RB_CORE_INFO("Version: %s", glGetString(GL_VERSION));

    //------ Setting Callbacks ---------
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
		// RB_CORE_INFO("Frame Resize: %d %d", width, height);

		Application* app = Application::GetInstance();
		app->WIDTH = width;
		app->HEIGHT = height;
		app->OnScreenResize();
    });

    input.reset( new Input(window) );
    if (cursorEnabled)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    else
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    return 1;
}

void Application::Run() 
{
    if (!initSuccess) return ;
    OnStart();

    // Main Varibles
	float lastFrameTime = glfwGetTime();
	float fpsTimer = lastFrameTime;
    const bool showFPS = false;
	glEnable(GL_DEPTH_TEST);

	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
        // Updating Time
        {
            float thisFrameTime = glfwGetTime();
			deltaTime = thisFrameTime - lastFrameTime;
			lastFrameTime = thisFrameTime;

			if (thisFrameTime - fpsTimer >= 1) {
				fpsTimer++;
				if (showFPS)
					RB_CORE_TRACE("FPS: %d", fps);
				fps = 0;
			}
			fps++;
        }

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        OnInput();
        OnRender();
		glfwPollEvents();
		glfwSwapBuffers(window);
    }
}
