#include "framework.h"
#include "Quad.h"

Quad::Quad(Vector2 m_size)
    : GameObject(L"Basic/Texure.hlsl")
{
    m_mesh = new Mesh<VertexType>();
    MakeMesh();
    m_mesh->CreateMesh();
}

Quad::Quad(wstring file)
    : GameObject(L"Basic/Texure.hlsl")
{
    Texture* texture = Texture::Add(file);
    m_material->SetDiffuseMap(file);
    m_size = texture->GetSize();

    m_mesh = new Mesh<VertexType>();
    MakeMesh();
    m_mesh->CreateMesh();
}

void Quad::Render()
{
    if (!Active()) return;

    SetRender();
    m_mesh->Draw();
}

void Quad::SetRender()
{
    m_mesh->GetVertexBuffer()->Set();
    m_mesh->GetIndexBuffer()->Set();
    GameObject::Render();
}

void Quad::MakeMesh()
{
    float left      = -m_size.x * 0.5f;
    float right     = +m_size.x * 0.5f;
    float top       = +m_size.y * 0.5f;
    float bottom    = -m_size.y * 0.5f;

    vector<VertexType>& vertices = m_mesh->GetVertices();

    vertices.emplace_back(left, top,     0, 0, 0);
    vertices.emplace_back(right, top,    0, 1, 0);
    vertices.emplace_back(left, bottom,  0, 0, 1);
    vertices.emplace_back(right, bottom, 0, 1, 1);

    vector<UINT>& indices = m_mesh->GetIndices();
    indices = { 0, 1, 2, 2, 1, 3 };
}
