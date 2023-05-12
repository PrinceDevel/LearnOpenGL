#include "ModelApp.hpp"


ModelApp::ModelApp(const unsigned int width, const unsigned int height, const char* name) : Application(width, height, name)
{

}
ModelApp::~ModelApp()
{

}


void ModelApp::OnStart() 
{
    // Creating Shapes
    {
        // Some Info
        int MaxVertexAttrib;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &MaxVertexAttrib);
        RB_CORE_INFO( "MAX VERTEX ATTRIBS: %d", MaxVertexAttrib);
        
        // Creating Shader
        modelShader.reset(new Shader(
            "resource/Shaders/BasicShader.vs",
            "resource/Shaders/BasicShader.fs"
        ));

        model.reset(FileSystem::ModelOBJ::Load("resource/Models/Cube.obj"));


        uint32_t index = 0;
        uint32_t faceCount = 1;
        float* vertices = new float[model->m_Faces.size() * 3 * 8];

        #define TRACE_PRINT RB_TRACE("ModelApp", "Face %d:  %f %f %f", faceCount, vertices[index-8], vertices[index-7], vertices[index-6])
        for (auto face: model->m_Faces)
        {
            // Vertex 1
            // Position
            vertices[index++] = model->m_Vertexes[face[0]].x;
            vertices[index++] = model->m_Vertexes[face[0]].y;
            vertices[index++] = model->m_Vertexes[face[0]].z;
            // Normal
            vertices[index++] = 0;
            vertices[index++] = 0;
            vertices[index++] = 0;
            // Texture Coordintes
            vertices[index++] = 0;
            vertices[index++] = 0;
            TRACE_PRINT;

            // Vertex 2
            // Position
            vertices[index++] = model->m_Vertexes[face[3]].x;
            vertices[index++] = model->m_Vertexes[face[3]].y;
            vertices[index++] = model->m_Vertexes[face[3]].z;
            // Normal
            vertices[index++] = 0;
            vertices[index++] = 0;
            vertices[index++] = 0;
            // Texture Coordintes
            vertices[index++] = 0;
            vertices[index++] = 0;
            TRACE_PRINT;

            // Vertex 3
            // Position
            vertices[index++] = model->m_Vertexes[face[6]].x;
            vertices[index++] = model->m_Vertexes[face[6]].y;
            vertices[index++] = model->m_Vertexes[face[6]].z;
            // Normal
            vertices[index++] = 0;
            vertices[index++] = 0;
            vertices[index++] = 0;
            // Texture Coordintes
            vertices[index++] = 0;
            vertices[index++] = 0;
            TRACE_PRINT;
            faceCount++;
        }
        #undef TRACE_PRINT
        RB_INFO("ModelApp", "Index: %d == %d", index, model->m_Faces.size() * 3 * 8);


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

    modelShader->Use();
    Mat4F modelTransform = Mat4F(1.0f);
    Vec3F modelPos = Vec3F(0.0f, 0.0f, 4.0f);
    Vec3F modelColor = Vec3F(1.0f, 0.3f, 1.0f);
    modelTransform = glm::translate(modelTransform, modelPos);
    modelTransform = glm::scale(modelTransform, Vec3F(1.0f, 1.0f, 1.0f));
    modelShader->setMat4("projection", projection);
    modelShader->setMat4("transform", modelTransform);
    modelShader->setVec3("uColor", modelColor);
}
void ModelApp::OnInput() 
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
void ModelApp::OnRender() 
{
    VAO->Bind();
    
    modelShader->Use();
    modelShader->setMat4("view", camera->GetViewMatrix());
    glDrawArrays(GL_TRIANGLES, 0, model->m_Faces.size() * 3);
    // VAO->DrawElements();

    // boxShader->Use();
    // boxShader->setMat4("view", camera->GetViewMatrix());
    // boxShader->setVec3("viewPos", camera->Position);
    // glDrawArrays(GL_TRIANGLES, 0, 36);
    // VAO->DrawElements();
}


void ModelApp::OnScreenResize ()
{
    projection = glm::perspective (
        glm::radians(45.0f),
        (float) WIDTH / (float) HEIGHT, 
        0.1f, 100.00f
    );
    modelShader->setMat4("projection", projection);
    // boxShader->setMat4("projection", projection);
}


Application* CreateApplication()
{
    return new ModelApp(960, 540, "BASIC APP");
}