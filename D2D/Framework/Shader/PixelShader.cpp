#include "Framework.h"

PixelShader::PixelShader(wstring file)
{
    m_file = file;
    ID3DBlob* outerror = nullptr;

    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    D3DCompileFromFile(file.c_str(),
        nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_5_0", flags, 0, &m_blob, &outerror);

    if (outerror)
    {
        OutputError(outerror);
        assert(false);
    }

    DEVICE->CreatePixelShader(m_blob->GetBufferPointer(),
        m_blob->GetBufferSize(), nullptr, &m_shader);
}

PixelShader::~PixelShader()
{
    m_shader->Release();
}

void PixelShader::Set()
{
    DC->PSSetShader(m_shader, nullptr, 0);
}

void PixelShader::OutputError(ID3DBlob* outerror)
{
    string str = (char*)outerror->GetBufferPointer();
    MessageBoxA(NULL, str.c_str(), "Error", MB_OK);
}
