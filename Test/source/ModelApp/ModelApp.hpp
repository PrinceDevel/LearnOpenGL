#include <Application.hpp>

#include <Graphics/Texture/Shader.hpp>
#include <Graphics/Texture/Texture.hpp>

#include <Graphics/Buffers/Buffer.hpp>
#include <Graphics/Buffers/VertexArray.hpp>
#include <Graphics/Camera.hpp>
#include <FileSystem/3D/ModelOBJ.hpp>

#include <Maths.hpp>

class ModelApp: public Application
{
public:
    
    ModelApp(const unsigned int width, const unsigned int height, const char* name);
    virtual ~ModelApp() override;

    virtual void OnRender() override;
    virtual void OnInput()  override;
    virtual void OnStart()  override;

    // Callbacks
    virtual void OnScreenResize() override;

private:
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Shader> modelShader;

    std::shared_ptr<FileSystem::ModelOBJ> model;
	std::unique_ptr<VertexArray> VAO;
	std::shared_ptr<VertexBuffer> VBO;

    Mat4F projection;
};