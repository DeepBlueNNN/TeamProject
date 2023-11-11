#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"


struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

PixelInput VS(VertexUV input)
{
    PixelInput ouput;
    ouput.pos = mul(input.pos, world);
    ouput.pos = mul(ouput.pos, view);
    ouput.pos = mul(ouput.pos, projection);
    ouput.uv = input.uv;
    return ouput;
 
}

float4 PS(PixelInput input) : SV_Target
{
    return mDiffuse;

}
