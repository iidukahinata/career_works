#include "Core/Core.hlsli"
#include "Core/Light.hlsli"

struct VS_IN {
    float4 pos : POSITION;
    float3 normal : NORMAL;
    float3 tangent  : TANGENT;
    float3 biNormal : BINORMAL;
    float2 tex : TEXCOORD0;
};

struct VS_OUT {
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float3 tangent  : TANGENT;
	float3 biNormal : BINORMAL;
    float4 worldPos : TEXCOORD0;
	float2 tex : TEXCOORD1;
    float3 toEye : TEXCOORD2;
    float4 viewPos : TEXCOORD3;
};

VS_OUT main(VS_IN input)
{
    VS_OUT output;

    // ���[���h��Ԃ̈ʒu�擾
    output.worldPos = mul(input.pos, world);

    // �J������Ԃ̈ʒu�擾
    output.viewPos = mul(output.worldPos, view);

    output.pos = output.viewPos;
    output.pos = mul(output.pos, projection);

    // �J���������ւ̃x�N�g���v�Z
    output.toEye = normalize(gEyePos - output.worldPos);
    
    output.normal = normalize(mul(world, input.normal));
    output.tangent = normalize(mul(world, input.tangent));
    output.biNormal = normalize(mul(world, input.biNormal));

    output.tex = input.tex;

    return output;
}