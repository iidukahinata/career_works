#include "PBR.hlsli"

struct PS_IN {
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float3 tangent  : TANGENT;
	float3 biNormal : BINORMAL;
	float4 worldPos : TEXCOORD0;
	float2 tex : TEXCOORD1;
	float3 toEye : TEXCOORD2;
	float4 viewPos : TEXCOORD3;
};

struct PS_OUT {
	float4 color : SV_TARGET0;
	float depth : SV_TARGET1;
};

float3 GetNormalsFromNormalMaps(float3 normal, float3 tangent, float3 biNormal, float2 tex)
{
	float3 binSpaceNormal = g_normalMap.SampleLevel(g_sampler, tex, 0.f).xyz;
	binSpaceNormal = (binSpaceNormal * 2.f) - 1.f;
	return tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y + normal * binSpaceNormal.z;
}

PS_OUT main(PS_IN input)
{
	float4 finalColor = float4(0, 0, 0, 1);

	Material material = GetMaterial(input.tex);
	float3 normal = GetNormalsFromNormalMaps(input.normal, input.tangent, input.biNormal, input.tex);

	// 平行光源計算
	finalColor.xyz += PBR(material, ToLightFromDirectionalLight(directionalLight), input.toEye, normal);

	// ポイントライト計算
	const int pointLightCount = lightCount.x;
	for (int i = 0; i < pointLightCount; ++i)
	{
		finalColor.xyz += PBR(material, ToLightFromPointLight(pointLights[i], input.worldPos), input.toEye, normal);
	}

	// スポットライト計算
	const int spotLightCount = lightCount.y;
	for (int i = 0; i < spotLightCount; ++i)
	{
		finalColor.xyz += PBR(material, ToLightFromSpotLight(spotLights[i], input.worldPos), input.toEye, normal);
	}

	// 2022/04/16 カラー値が0以下になる現象を発見一時的にmax値で対処
	finalColor.x = max(finalColor.x, 0.f);
	finalColor.y = max(finalColor.y, 0.f);
	finalColor.z = max(finalColor.z, 0.f);

	finalColor.xyz += (ambientColor.xyz * material.albedoColor);
	
	PS_OUT output;
	output.color = finalColor;
	output.depth = input.viewPos.z;
	
	return output;
}