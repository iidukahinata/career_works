Texture2D g_texture : register(t0);
sampler g_sampler : register(s0);

cbuffer ConstBufferColor : register(b0)
{
	float4 color;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD;
};

float4 main(PS_IN input) : SV_TARGET
{
	return g_texture.Sample(g_sampler, input.tex) * color;
}