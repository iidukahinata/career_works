Texture2D g_texture;
sampler g_sampler;

cbuffer ConstBufferColor : register(b3)
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