#include <Application.hpp>

#include <Graphics/Texture/Shader.hpp>
#include <Graphics/Texture/Texture.hpp>

#include <Graphics/Buffers/Buffer.hpp>
#include <Graphics/Buffers/VertexArray.hpp>
#include <Graphics/Camera.hpp>

#include <Maths.hpp>


class BasicApp: public Application
{
public:
    
    BasicApp(const unsigned int width, const unsigned int height, const char* name);
    virtual ~BasicApp() override;

    virtual void OnRender() override;
    virtual void OnInput()  override;
    virtual void OnStart()  override;

    // Callbacks
    virtual void OnScreenResize() override;

private:
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Shader> lightShader;
    std::unique_ptr<Shader> boxShader;

	std::unique_ptr<VertexArray> VAO;
	std::shared_ptr<VertexBuffer> VBO;
	std::shared_ptr<IndexBuffer> IBO;

    Mat4F projection;
};