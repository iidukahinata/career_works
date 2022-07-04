#include "Blur.hlsli"

float4 main(PS_IN input) : SV_TARGET
{
    float4 tex[8] = {
        input.tex1, input.tex2, input.tex3, input.tex4,
        input.tex5, input.tex6, input.tex7, input.tex8
    };

    float w[8] = {
        weights[0].x, weights[0].y, weights[0].z, weights[0].w,
        weights[1].x, weights[1].y, weights[1].z, weights[1].w
    };

    float4 finalColor = float4(0.f, 0.f, 0.f, 0.f);    
    for (int i = 0; i < 8; i++)
	{
		finalColor += (g_texture.Sample(g_sampler, tex[i].xy) + g_texture.Sample(g_sampler, tex[i].zw)) * w[i];
	}

	finalColor.a = 1.f;
	return finalColor;
}