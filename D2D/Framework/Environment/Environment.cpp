#include "Framework.h"
#include "Environment.h"

Environment::Environment()
{
    CreateProjection();
    CreateState();

    mainCamera  = new Camera();
    lightBuffer = new LightBuffer();
    viewBuffer  = new ViewBuffer();    
}

Environment::~Environment()
{
    SAFE_DELETE(projectionBuffer);  
    SAFE_DELETE(lightBuffer);
    SAFE_DELETE(viewBuffer);

    SAFE_DELETE(mainCamera);

    SAFE_DELETE(samplerState);
    SAFE_DELETE(rasterizerState[0]);
    SAFE_DELETE(rasterizerState[1]);
    SAFE_DELETE(blendState[0]);
    SAFE_DELETE(blendState[1]);
}

void Environment::Update()
{
    if (KEY_DOWN(VK_F1))
        isWireMode = !isWireMode;

    if (KEY_DOWN(VK_F2))
        Collider::RenderOnOff();

    mainCamera->Update();
}

void Environment::GUIRender()
{
    if (ImGui::TreeNode("Environment"))
    {
        mainCamera->GUIRender();
        ImGui::Text("LightOption");
        for (UINT i = 0; i < lightBuffer->Get().lightCount; i++)
        {
            string name = "Light_" + to_string(i);
            if (ImGui::TreeNode(name.c_str()))
            {
                ImGui::ColorEdit3("LightColor", (float*)&lightBuffer->Get().lights[i].color, ImGuiColorEditFlags_PickerHueWheel);
                ImGui::SliderFloat3("LightDir", (float*)&lightBuffer->Get().lights[i].direction, -1, 1);

                ImGui::TreePop();
            }
        }
        
        ImGui::ColorEdit3("AmbientLight", (float*)&lightBuffer->Get().ambientLight, ImGuiColorEditFlags_PickerHueWheel);
        ImGui::ColorEdit3("AmbientCeil", (float*)&lightBuffer->Get().ambientCeil, ImGuiColorEditFlags_PickerHueWheel);
        ImGui::TreePop();
    }    
}

void Environment::Set()
{
    SetViewport();
    SetPerspective();

    if (isWireMode)
        rasterizerState[1]->SetState();
    else
        rasterizerState[0]->SetState();

    blendState[0]->SetState();
    depthStencilState[0]->SetState();

    lightBuffer->SetPS(0);
}

void Environment::PostSet()
{
    viewBuffer->SetVS(1);
    SetOrthographic();

    blendState[1]->SetState();
    depthStencilState[1]->SetState();
}

void Environment::SetViewport(UINT width, UINT height)
{
    viewport.Width = width;
    viewport.Height = height;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;

    DC->RSSetViewports(1, &viewport);
}

void Environment::SetPerspective()
{
    projectionBuffer->Set(perspective);
    projectionBuffer->SetVS(2);
}

void Environment::SetOrthographic()
{
    projectionBuffer->Set(orthographic);
    projectionBuffer->SetVS(2);
}

void Environment::CreateProjection()
{
    orthographic = XMMatrixOrthographicOffCenterLH(
        0.0f, MAIN->GetWidth(), 0.0f, MAIN->GetHeight(), -1.0f, 1.0f);
    
    perspective = XMMatrixPerspectiveFovLH(XM_PIDIV4,
        (float)MAIN->GetWidth() / (float)MAIN->GetHeight(), 0.1f, 1000.0f);

    projectionBuffer = new MatrixBuffer();    
}

void Environment::CreateState()
{
    samplerState = new SamplerState();
    samplerState->SetState();

    rasterizerState[0] = new RasterizerState();
    rasterizerState[1] = new RasterizerState();
    rasterizerState[1]->FillMode(D3D11_FILL_WIREFRAME);

    blendState[0] = new BlendState();
    blendState[1] = new BlendState();
    blendState[1]->Alpha(true);

    depthStencilState[0] = new DepthStencilState();
    depthStencilState[1] = new DepthStencilState();
    depthStencilState[1]->DepthEnable(false);
}
