#include "../PBR/PBR.hlsli"

Texture2D<float4> g_colorTex	 : register(t1);
Texture2D<float4> g_normalTex	 : register(t2);
Texture2D<float2> g_depthTex	 : register(t3);
Texture2D<float4> g_parameterTex : register(t4);

struct PS_IN 
{
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
	
	int4 texCoord = int4(((worldPos * gInvScale) + gBias).xyz, 0);
	uint lightData = g_lightDataTex.Load(texCoord);
	uint lightIndex = lightData.x;
	//const uint pointLightCount = lightData.y & 0xFFFF;
	//const uint spotLightCount = lightData.y >> 16;
	const uint pointLightCount = gLightCount.x;
	const uint spotLightCount = gLightCount.y;
	
	// マテリアル生成
	Material material;
	material.albedoColor = color;
	material.metallic = param.z;
	material.roughness = param.w;

	// 平行光源計算
	finalColor.xyz += PBR(material, ToLightFromDirectionalLight(gDirectionalLight), toEye, normal.xyz);
	
	// ポイントライト計算
	for (uint i = 0; i < pointLightCount; ++i)
	{
		const int index = gLightIndices[lightIndex++];
		
		finalColor.xyz += PBR(material, ToLightFromPointLight(gPointLights[i], worldPos), toEye, normal.xyz);
	}

	// スポットライト計算
	for (uint i = 0; i < spotLightCount; ++i)
	{
		const int index = gLightIndices[lightIndex++];
		
		finalColor.xyz += PBR(material, ToLightFromSpotLight(gSpotLights[index], worldPos), toEye, normal.xyz);
	}

	finalColor.xyz += (gAmbientColor.xyz * color.xyz);
	return finalColor;
}