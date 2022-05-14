#include "psvsCommon.hlsli"
#include "Light.hlsli"

#define PI 3.141592654

Texture2D g_texture;
sampler g_sampler;

struct PS_IN {
	float4 pos : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 toEye : TEXCOORD1;
	float4 worldPos : TEXCOORD2;
	float4 viewPos : TEXCOORD3;
};

struct PS_OUT {
	float4 color : SV_TARGET0;
	float depth : SV_TARGET1;
};

PS_OUT main(PS_IN input)
{
	float3 lightDirection = normalize(directionalLight.direction);
	float lightPower = saturate(dot(input.normal, lightDirection));

	// 正規化ランバート拡散反射光
	float diffuse = directionalLight.color * lightPower / PI;

	// 鏡面反射の強さ
	float3 reflection = reflect(lightDirection, input.normal);
	lightPower = saturate(dot(reflection, input.toEye));
	lightPower = pow(lightPower, 5.0f);

	// 鏡面反射光
	float3 specular = directionalLight.color * lightPower;

	// 最終的な光
	float3 light = diffuse + specular;
	light += 0.4f;

	float4 finalColor = g_texture.Sample(g_sampler, input.tex);
	finalColor.xyz *= light;

	PS_OUT output;
	output.color = finalColor;
	output.depth = input.viewPos.z;

	return output;
}