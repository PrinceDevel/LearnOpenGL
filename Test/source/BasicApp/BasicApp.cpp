#include "BasicApp.hpp"


BasicApp::BasicApp(const unsigned int width, const unsigned int height, const char* name) : Application(width, height, name)
{

}
BasicApp::~BasicApp()
{

}


void BasicApp::OnStart() 
{
    // Creating Shapes
    {
        // Some Info
        int MaxVertexAttrib;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &MaxVertexAttrib);
        RB_CORE_INFO( "MAX VERTEX ATTRIBS: %d", MaxVertexAttrib);
        
        // Creating Shader
        lightShader.reset(new Shader(
            "resource/Shaders/BasicShader.vs",
            "resource/Shaders/BasicShader.fs"
        ));
        boxShader.reset(new Shader(
            "resource/Shaders/Illumination.vs",
            "resource/Shaders/Illumination.fs"
        ));

        float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
        };


        // Layout of Vertex Data
        BufferLayout cubelayout = {
            { ShaderDataType::Vec3F, "aPosition" },
            { ShaderDataType::Vec3F, "aNormal" },
            { ShaderDataType::Vec2F, "aTexture" }
        };

        // Setting up buffers
        VAO.reset(new VertexArray());
        VAO->Bind();

        VBO.reset(new VertexBuffer(vertices, (unsigned int) sizeof(vertices)));
        VBO->SetLayout(cubelayout);
        VAO->AddVertexBuffer(VBO);
        
        // IBO.reset(new IndexBuffer(indices, sizeof(indices) / sizeof(unsigned int)));
        // VAO->SetIndexBuffer(IBO);
    }


    // World Setup
    projection = glm::perspective (
        glm::radians(45.0f),
        (float) WIDTH / (float) HEIGHT, 
        0.1f, 100.00f
    );
    camera.reset(new Camera(
        Vec3F(0.0f, 0.0f, 10.0f)
    ));

    lightShader->Use();
    Mat4F lightTransform = Mat4F(1.0f);
    Vec3F lightPos = Vec3F(0.0f, 0.0f, 4.0f);
    Vec3F lightColor = Vec3F(1.0f, 1.0f, 1.0f);
    lightTransform = glm::translate(lightTransform, lightPos);
    lightTransform = glm::scale(lightTransform, Vec3F(0.3f, 0.3f, 0.3f));
    lightShader->setMat4("projection", projection);
    lightShader->setMat4("transform", lightTransform);
    lightShader->setVec3("uColor", lightColor);

    boxShader->Use();
    Mat4F boxTransform = Mat4F(1.0f);
    Vec3F boxPos = Vec3F(0.0f, 0.0f, 1.0f);
    boxTransform = glm::translate(boxTransform, boxPos);
    boxTransform = glm::scale(boxTransform, Vec3F(2.0f, 2.0f, 2.0f));
    boxShader->setMat4("projection", projection);
    boxShader->setMat4("transform", boxTransform);
    Vec3F diffuseColor = lightColor   * Vec3F(0.5f); // decrease the influence
    Vec3F ambientColor = diffuseColor * Vec3F(0.2f); // low influence
    boxShader->setVec3("light.position", lightPos);
    boxShader->setVec3("light.ambient", ambientColor);
    boxShader->setVec3("light.diffuse", diffuseColor);
    boxShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    boxShader->setVec3("material.ambient", 0.2f, 0.2f, 0.8f);
    boxShader->setVec3("material.diffuse", 0.2f, 0.2f, 0.8f);
    boxShader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
    boxShader->setFloat("material.shininess", 32.0f);
}
void BasicApp::OnInput() 
{
    input->Update();
                
    if (!cursorEnabled)
        camera->Update(input->GetCursorMove());

    if (input->IsKeyPressed(RB_VK_ESCAPE))
        glfwSetWindowShouldClose(window, true);

    if (input->IsKeyPressed(RB_VK_TAB)) {
        if (cursorEnabled)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else 
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        cursorEnabled = !cursorEnabled;
    }

    const float velocity = camera->MoveSpeed * deltaTime;
    if (input->IsKeyPressed(RB_VK_W))
        camera->Position += camera->Front * velocity;
    if (input->IsKeyPressed(RB_VK_S))
        camera->Position -= camera->Front * velocity;
    if (input->IsKeyPressed(RB_VK_A))
        camera->Position -= camera->Right * velocity;
    if (input->IsKeyPressed(RB_VK_D))
        camera->Position += camera->Right * velocity;
}
void BasicApp::OnRender() 
{
    VAO->Bind();
    
    lightShader->Use();
    lightShader->setMat4("view", camera->GetViewMatrix());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // VAO->DrawElements();

    boxShader->Use();
    boxShader->setMat4("view", camera->GetViewMatrix());
    boxShader->setVec3("viewPos", camera->Position);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // VAO->DrawElements();
}


void BasicApp::OnScreenResize ()
{
    projection = glm::perspective (
        glm::radians(45.0f),
        (float) WIDTH / (float) HEIGHT, 
        0.1f, 100.00f
    );
    boxShader->setMat4("projection", projection);
    lightShader->setMat4("projection", projection);
}


Application* CreateApplication()
{
    return new BasicApp(960, 540, "BASIC APP");
}