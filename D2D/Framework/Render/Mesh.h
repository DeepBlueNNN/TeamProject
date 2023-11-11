#pragma once
template<typename T>
class Mesh
{
public:
	Mesh() = default;  // 시스템에서 사용되는 기본생성자를 사용 : ShallowCopy
	~Mesh();

	void Draw(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	void CreateMesh();
	void UpdateVertex(void* data, UINT count);
	void UpdateVertex();
	void UpdateIndex();

	vector<T>&    GetVertices() { return vertices; }
	vector<UINT>& GetIndices()  { return indices; }
	VertexBuffer* GetVertexBuffer() { return vertexBuffer; }
	IndexBuffer*  GetIndexBuffer()  { return indexBuffer; }


private:
	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer*  indexBuffer = nullptr;
	vector<T> vertices;
	vector<UINT> indices;
};

template<typename T>
inline Mesh<T>::~Mesh()
{
	SAFE_DELETE(vertexBuffer);
	SAFE_DELETE(indexBuffer);
}

template<typename T>
inline void Mesh<T>::Draw(D3D11_PRIMITIVE_TOPOLOGY type)
{
	vertexBuffer->Set(type);
	if (indexBuffer)
	{
		indexBuffer->Set();
		DC->DrawIndexed((UINT)indices.size(), 0, 0);
	}
	else
	{
		DC->Draw((UINT)vertices.size(), 0);
	}
}

template<typename T>
inline void Mesh<T>::CreateMesh()
{
	if (vertices.size() > 0)
	{
		vertexBuffer = new VertexBuffer(vertices.data(),
			sizeof(T), (UINT)vertices.size());
	}

	if (indices.size() > 0)
	{
		indexBuffer = new IndexBuffer(indices.data(),
			   (UINT)indices.size());
	}

}

template<typename T>
inline void Mesh<T>::UpdateVertex(void* data, UINT count)
{
	vertexBuffer->Update(data, count);
}

template<typename T>
inline void Mesh<T>::UpdateVertex()
{
	vertexBuffer->Update(vertices.data(), vertices.size());
	vertexBuffer->Set();
}

template<typename T>
inline void Mesh<T>::UpdateIndex()
{
	indexBuffer->Update(indices.data(), indices.size());
	indexBuffer->Set();
}
