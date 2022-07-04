Texture2D g_texture;
sampler g_sampler;

struct PS_IN {
	float4 pos : POSITION;
	float2 tex : TEXCOORD;
};

float4 main(PS_IN input) : SV_TARGET
{
	float4 finalColor = g_texture.Sample(g_sampler, input.tex);

	float t = dot(finalColor.xyz, float3(0.2125f, 0.7154f, 0.0721f));
	if ((t - 1.f) > 0) {
		return finalColor;
	}
	return float4(0, 0, 0, 0);
}