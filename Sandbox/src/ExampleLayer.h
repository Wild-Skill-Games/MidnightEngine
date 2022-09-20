#pragma once

#include <MidnightEngine.h>

class ExampleLayer : public MidnightEngine::Layer
{
public:
    ExampleLayer();

    virtual void OnUpdate(MidnightEngine::Timestep ts) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MidnightEngine::Event &event) override;

private:
    MidnightEngine::ShaderLibrary m_ShaderLibrary;

    MidnightEngine::Ref<MidnightEngine::Shader> m_TriangleShader;
    MidnightEngine::Ref<MidnightEngine::VertexArray> m_TriangleVertexArray;

    MidnightEngine::Ref<MidnightEngine::Shader> m_SquareShader;
    MidnightEngine::Ref<MidnightEngine::VertexArray> m_SquareVertexArray;

    MidnightEngine::Ref<MidnightEngine::Texture2D> m_Texture2D, m_LogoTexture;

    MidnightEngine::OrthographicCameraController m_CameraController;

    glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};