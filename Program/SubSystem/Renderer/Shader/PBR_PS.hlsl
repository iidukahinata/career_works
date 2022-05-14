#include "psvsCommon.hlsli"
#include "PBR.hlsli"

Texture2D g_texture : register(t0);
Texture2D g_normalMap : register(t1);
Texture2D g_metallicSmoothMap : register(t2); // r�Ƀ��^���b�N�Aa�ɃX���[�X
sampler g_sampler;

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

	// �T���v���擾
	float4 albedoColor = g_texture.Sample(g_sampler, input.tex);
	float4 metallicSmooth = g_metallicSmoothMap.Sample(g_sampler, input.tex);
	float metallic = metallicSmooth.r;
	float smooth = metallicSmooth.a;

	// �}�e���A������
	Material material;
	material.albedoColor = albedoColor.xyz;
	material.roughness = (1.f - smooth); // ���炩�� �� �e�� �ɕύX
	material.metallic = metallic;

	// �@���擾
	float3 normal = GetNormalsFromNormalMaps(input.normal, input.tangent, input.biNormal, input.tex);

	// ���s�����v�Z
	finalColor.xyz += PBR(material,
						  ToLightFromDirectionalLight(directionalLight),
						  input.toEye,
						  normal);

	// �|�C���g���C�g�v�Z
	for (int i = 0; i < lightCount.x; i++)
	{
		finalColor.xyz += PBR(material,
							  ToLightFromPointLight(pointLights[i], input.worldPos),
							  input.toEye,
							  normal);
	}

	// �X�|�b�g���C�g�v�Z
	for (int i = 0; i < lightCount.y; i++)
	{
		finalColor.xyz += PBR(material,
							  ToLightFromSpotLight(spotLights[i], input.worldPos),
							  input.toEye,
							  normal);
	}
		
	// 2022/04/16 �J���[�l��0�ȉ��ɂȂ錻�ۂ𔭌��ꎞ�I��max�l�őΏ�
	finalColor.x = max(finalColor.x, 0.f);
	finalColor.y = max(finalColor.y, 0.f);
	finalColor.z = max(finalColor.z, 0.f);

	finalColor.xyz += (ambientColor * albedoColor);
	
	PS_OUT output;
	output.color = finalColor;
	output.depth = input.viewPos.z;
	
	return output;
}