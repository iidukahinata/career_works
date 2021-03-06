#include "../PBR/PBR.hlsli"

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
};

struct PS_OUT 
{
	float4 color : SV_TARGET0;
	float4 normal : SV_TARGET1;
	float2 depth : SV_TARGET2;
	float4 param : SV_TARGET3;
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

PS_OUT main(PS_IN input)
{
	float4 finalColor = float4(0, 0, 0, 1);

	Material material = GetMaterial(input.tex);
	float3 normal = GetNormalsFromNormalMaps(input.normal, input.tangent, input.biNormal, input.tex);
	
	// GBuffer 作成
	PS_OUT output;	
	output.color = float4(material.albedoColor, 1.f);
	output.normal = float4(normal, 1.f);
	output.depth = float2(input.pos.z / input.worldPos.w, input.worldPos.z);
	output.param = float4(input.worldPos.x, input.worldPos.y, material.metallic, material.roughness);
	
	return output;
}