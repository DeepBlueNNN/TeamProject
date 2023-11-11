#pragma once

class PixelShader : public Shader
{
private:
    friend class Shader;

    PixelShader(wstring file);
    ~PixelShader();

public:
    virtual void Set() override;

private:
    void  OutputError(ID3DBlob* outerror);

private:
    ID3D11PixelShader* m_shader;    
};