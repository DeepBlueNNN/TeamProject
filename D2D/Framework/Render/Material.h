#pragma once
class  Material
{
public:
	Material();
	Material(wstring shaderFile);
	~Material();

public:
	void Set();
	void GUIRender();
	void SetShader(wstring shaderFile);
	void SetDiffuseMap(wstring textureFile);
	void SetSpecularMap(wstring textureFile);
	void SetNormalMap(wstring textureFile);

public:
	void Save(string file);
	void Load(string file);


public:
	string& GetName() { return name; }
	MaterialBuffer::Data& GetData() { return buffer->Get(); }
private:
	void		ParsingShader(tinyxml2::XMLNode* Parent);
	void		ParsingTexture(tinyxml2::XMLNode* Parent);
	void		ParsingProperty(tinyxml2::XMLNode* Parent);
	Float4      ParsingColor(tinyxml2::XMLNode* Parent);
private:
	string name;

	VertexShader* vertexShader = nullptr;
	PixelShader*  pixelShader  = nullptr;
	Texture*      diffuseMap   = nullptr;
	Texture*      specularMap  = nullptr;
	Texture*      normalMap    = nullptr;

private:
	MaterialBuffer* buffer = nullptr;
	string          file;

};