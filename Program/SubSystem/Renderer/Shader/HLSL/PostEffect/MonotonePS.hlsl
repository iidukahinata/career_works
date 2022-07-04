Texture2D g_texture;
sampler g_sampler;

struct PS_IN {
	float4 pos : POSITION;
	float2 tex : TEXCOORD;
};

float4 main(PS_IN input) : SV_TARGET
{
	float4 finalColor = g_texture.Sample(g_sampler, input.tex);

	// ÉÇÉmÉNÉçâª
	finalColor.xyz = 0.299f * finalColor.x + 0.587f * finalColor.y + 0.114f * finalColor.z;
	return finalColor;
}