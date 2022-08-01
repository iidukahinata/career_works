#include "PBR.hlsli"

Texture2D g_texture : register(t1);
Texture2D g_normalMap : register(t2);
Texture2D g_metallicSmoothMap : register(t3); // rにメタリック、aにスムース

struct PS_IN
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 biNormal : BINORMAL;
	float2 tex : TEXCOORD0;
	float4 worldPos : TEXCOORD1;
	float4 viewPos : TEXCOORD2;
	float3 toEye : TEXCOORD3;
};

Material GetMaterial(float2 tex)
{
	// サンプル取得
	float4 albedoColor = g_texture.Sample(g_sampler, tex);
	float4 metallicSmooth = g_metallicSmoothMap.Sample(g_sampler, tex);
	float metallic = metallicSmooth.r;
	float smooth = metallicSmooth.a;

	// マテリアル生成
	Material material;
	material.albedoColor = albedoColor.xyz;
	material.metallic = metallic;
	material.roughness = (1.f - smooth); // 滑らかさ → 粗さ に変更
	
	return material;
}


float3 GetNormalsFromNormalMaps(float3 normal, float3 tangent, float3 biNormal, float2 tex)
{
	float3 binSpaceNormal = g_normalMap.SampleLevel(g_sampler, tex, 0.f).xyz;
	binSpaceNormal = (binSpaceNormal * 2.f) - 1.f;
	return tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y + normal * binSpaceNormal.z;
}

float4 main(PS_IN input) : SV_TARGET
{
	float4 finalColor = float4(0, 0, 0, 1);

	Material material = GetMaterial(input.tex);
	float3 normal = GetNormalsFromNormalMaps(input.normal, input.tangent, input.biNormal, input.tex);

	// 平行光源計算
	finalColor.xyz += PBR(material, ToLightFromDirectionalLight(gDirectionalLight), input.toEye, normal);

	// ポイントライト計算
	const int pointLightCount = gLightCount.x;
	for (int i = 0; i < pointLightCount; ++i)
	{
		finalColor.xyz += PBR(material, ToLightFromPointLight(gPointLights[i], input.worldPos), input.toEye, normal);
	}
	
	// スポットライト計算
	const int spotLightCount = gLightCount.y;
	for (int i = 0; i < spotLightCount; ++i)
	{
		finalColor.xyz += PBR(material, ToLightFromSpotLight(gSpotLights[i], input.worldPos), input.toEye, normal);
	}

	finalColor.xyz += (gAmbientColor.xyz * material.albedoColor);	
	return finalColor;
}