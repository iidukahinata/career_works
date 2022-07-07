#include "../PBR.hlsli"

Texture2D<float4> g_colorTex	 : register(t0);
Texture2D<float4> g_normalTex	 : register(t1);
Texture2D<float2> g_depthTex	 : register(t2);
Texture2D<float4> g_parameterTex : register(t3);

struct PS_IN {
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD;
};

float4 main(PS_IN input) : SV_TARGET
{
	float4 finalColor = float4(0, 0, 0, 1);
	
	float4 color = g_colorTex.Sample(g_sampler, input.tex);
	float4 normal = g_normalTex.Sample(g_sampler, input.tex);
	float2 depth = g_depthTex.Sample(g_sampler, input.tex);
	float4 param = g_parameterTex.Sample(g_sampler, input.tex);
	
	float4 worldPos = float4(param.x, param.y, depth.y, 0.f);
	float3 toEye = normalize(gEyePos - worldPos).xyz;
	
	// マテリアル生成
	Material material;
	material.albedoColor = color;
	material.metallic = param.z;
	material.roughness = param.w;

	// 平行光源計算
	finalColor.xyz += PBR(material, ToLightFromDirectionalLight(directionalLight), toEye, normal.xyz);

	// ポイントライト計算
	const int pointLightCount = lightCount.x;
	for (int i = 0; i < pointLightCount; ++i)
	{
		finalColor.xyz += PBR(material, ToLightFromPointLight(pointLights[i], worldPos), toEye, normal.xyz);
	}

	// スポットライト計算
	const int spotLightCount = lightCount.y;
	for (int i = 0; i < spotLightCount; ++i)
	{
		finalColor.xyz += PBR(material, ToLightFromSpotLight(spotLights[i], worldPos), toEye, normal.xyz);
	}

	finalColor.xyz += (ambientColor.xyz * color.xyz);
	
	return finalColor;
}