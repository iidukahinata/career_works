#include "Core.hlsli"

struct VS_IN {
	float4 pos : POSITION;
};

struct VS_OUT {
	float4 pos : SV_POSITION;
	float4 tex : TEXCOORD1;
	float4 viewPos : TEXCOORD2;
};

VS_OUT main(VS_IN input)
{
	VS_OUT output;
	
	output.pos = mul(input.pos, world);

    // ƒJƒƒ‰‹óŠÔ‚ÌˆÊ’uæ“¾
	output.viewPos = mul(output.pos, view);

	output.pos = output.viewPos;
	output.pos = mul(output.pos, projection);

	output.tex = input.pos;

	return output;
}