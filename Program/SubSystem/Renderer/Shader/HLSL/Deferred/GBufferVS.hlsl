#include "../Core/Core.hlsli"

struct VS_IN
{
	float4 pos : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 biNormal : BINORMAL;
	float2 tex : TEXCOORD0;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 biNormal : BINORMAL;
	float2 tex : TEXCOORD0;
	float4 worldPos : TEXCOORD1;
	float4 viewPos : TEXCOORD2;
};

VS_OUT main(VS_IN input)
{
	VS_OUT output;

    // äeãÛä‘ÇÃç¿ïWéÊìæ
	output.worldPos = mul(input.pos, world);
	output.viewPos = mul(output.worldPos, view);
	output.pos = mul(output.viewPos, projection);
    
	output.normal = normalize(mul(world, float4(input.normal, 0.f)));
	output.tangent = normalize(mul(world, float4(input.tangent, 0.f)));
	output.biNormal = normalize(mul(world, float4(input.biNormal, 0.f)));

	output.tex = input.tex;

	return output;
}