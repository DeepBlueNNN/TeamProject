#include "framework.h"
#include "ModelMesh.h"

ModelMesh::ModelMesh(string name)
{
	m_name = name;
}

ModelMesh::~ModelMesh()
{
	SAFE_DELETE(m_mesh);
}

void ModelMesh::Render()
{
	m_material->Set();
	m_mesh->Draw();
}

void ModelMesh::CreateMesh(void* vertexData, UINT vertexCount, void* indexData, UINT indexCount)
{
	m_mesh = new Mesh<ModelVertex>();

	m_mesh->GetVertices().resize(vertexCount);
	memcpy(m_mesh->GetVertices().data(), vertexData, sizeof(ModelVertex) * vertexCount);
	m_mesh->GetIndices().resize(indexCount);
	memcpy(m_mesh->GetIndices().data(), indexData, sizeof(UINT) * indexCount);

	m_mesh->CreateMesh();
}
