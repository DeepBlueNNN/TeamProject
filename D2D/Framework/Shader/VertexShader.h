#pragma once

class VertexShader : public Shader
{
private:
    friend class Shader;

    VertexShader(wstring file);
    ~VertexShader();

public:
    virtual void Set() override;

private:
    void CreateInputLayout();

private:
    void  OutputError(ID3DBlob* outerror);

private:
    ID3D11VertexShader* m_shader = nullptr;
    ID3D11InputLayout*  m_inputLayout = nullptr;

    ID3D11ShaderReflection* m_reflection = nullptr;
};