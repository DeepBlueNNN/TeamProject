#pragma once
class Quad : public GameObject
{
private:
	typedef VertexUV VertexType;
public:
	Quad(Vector2 size);
	Quad(wstring file);

public:
	void Render();
	void SetRender();

private:
	void MakeMesh();

private:
	Vector2 m_size;
	Mesh<VertexType>* m_mesh;

};