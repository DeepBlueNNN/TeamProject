#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"


LightPixelInput VS(VertexUVNormalTangent input)
{
    LightPixelInput output;
    output.pos = mul(input.pos, world);
	
    output.viewPos = invView._41_42_43;   // Camera : x,y,z
    output.worldPos = output.pos.xyz;         // 물체   : World좌표
	
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);

    output.uv = input.uv;
	
    output.normal   = mul(input.normal, (float3x3) world);
    output.tangent  = mul(input.tangent, (float3x3) world);
    output.binormal = cross(output.normal, output.tangent);
	
    return output;
}

float4 PS(LightPixelInput input) : SV_TARGET
{
    Material material = GetMaterial(input);
	
    // NormalMapping.hlsl에 있던 기능을 함수로
    float4 color    = CalcDirectional(material, lights[0]);
    float4 ambient  = CalcAmbient(material);
    float4 emissive = CalcEmissive(material);
	
    return color + ambient + emissive;
}