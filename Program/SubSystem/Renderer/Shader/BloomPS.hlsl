Texture2D g_texture0 : register(t0);
Texture2D g_texture1 : register(t1);
Texture2D g_texture2 : register(t2);
Texture2D g_texture3 : register(t3);
sampler g_sampler;

struct PS_IN {
	float4 pos : POSITION;
	float2 tex : TEXCOORD;
};

float4 main(PS_IN input) : SV_TARGET
{
	float4 finalColor = float4(0.f, 0.f, 0.f, 0.f);
	finalColor += g_texture0.Sample(g_sampler, input.tex);
	finalColor += g_texture1.Sample(g_sampler, input.tex);
	finalColor += g_texture2.Sample(g_sampler, input.tex);
	finalColor += g_texture3.Sample(g_sampler, input.tex);
	finalColor /= 4.f;

	finalColor.a = 1.f;
	return finalColor;
}