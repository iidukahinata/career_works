#include "Core/Core.hlsli"

struct VS_IN 
{
	float4 pos : POSITION;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float4 tex : TEXCOORD1;
	float4 viewPos : TEXCOORD2;
};

VS_OUT main(VS_IN input)
{
	VS_OUT output;
	
	// ƒJƒƒ‰‹óŠÔ‚ÌˆÊ’uæ“¾
	output.pos = mul(input.pos, gWorld);
	output.viewPos = mul(output.pos, gView);
	output.pos = mul(output.viewPos, gProjection);

	output.tex = input.pos;

	return output;
}