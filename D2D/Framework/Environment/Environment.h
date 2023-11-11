#pragma once

/////////////////////////////////////////////////////////////////
//                   Projection 생성 Class				       //
//              Rasterizer,Blend,Depth등을 Control             //
////////////////////////////////////////////////////////////////

class Environment : public Singleton<Environment>
{
private:
    friend class Singleton;

private:
    Environment();
    ~Environment();

public:
    void Update();
    void GUIRender();

public: // Getter
    Camera* GetMainCamera() { return mainCamera; }
    Matrix  GetProjection() { return perspective; }

public: // Setter
    void Set();
    void PostSet();

    void SetViewport(UINT width = MAIN->GetWidth(), UINT height = MAIN->GetHeight());
    void SetPerspective();
    void SetOrthographic();

private:
    void CreateProjection();
    void CreateState();

private:
    MatrixBuffer*       projectionBuffer     = nullptr;       
    LightBuffer*        lightBuffer          = nullptr;
    ViewBuffer*         viewBuffer           = nullptr;
    
    SamplerState*       samplerState         = nullptr;
    RasterizerState*    rasterizerState[2];
    BlendState*         blendState[2];
    DepthStencilState*  depthStencilState[2];

    D3D11_VIEWPORT      viewport;

    Matrix  perspective;
    Matrix  orthographic;
    Camera* mainCamera = nullptr;
    bool    isWireMode = false;
};