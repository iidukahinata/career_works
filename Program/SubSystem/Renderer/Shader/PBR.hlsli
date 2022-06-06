/*
* �����x�[�X�����_�����O���쐬����ɓ������Ă̎�ȎQ�l������URL
* Unreal Engine �Z�p����
* https://blog.selfshadow.com/publications/s2013-shading-course/karis/s2013_pbs_epic_notes_v2.pdf
* Disney
* https://blog.selfshadow.com/publications/s2012-shading-course/burley/s2012_pbs_disney_brdf_notes_v3.pdf
* �t�B�������g
* https://google.github.io/filament/Filament.md.html#overview/physicallybasedrendering
*/


#include "Core.hlsli"
#include "Light.hlsli"

Texture2D g_texture : register(t0);
Texture2D g_normalMap : register(t1);
Texture2D g_metallicSmoothMap : register(t2); // r�Ƀ��^���b�N�Aa�ɃX���[�X
sampler g_sampler;

struct Material
{
	float3 albedoColor;
	float roughness;
	float metallic;
};

Material GetMaterial(float2 tex)
{
	// �T���v���擾
	float4 albedoColor = g_texture.Sample(g_sampler, tex);
	float4 metallicSmooth = g_metallicSmoothMap.Sample(g_sampler, tex);
	float metallic = metallicSmooth.r;
	float smooth = metallicSmooth.a;

	// �}�e���A������
	Material material;
	material.albedoColor = albedoColor.xyz;
	material.roughness = (1.f - smooth); // ���炩�� �� �e�� �ɕύX
	material.metallic = metallic;
	
	return material;
}

// [Beckmann 1963]
float DistributionBeckmann(float NdotH, float a2)
{
	float NdotH2 = NdotH * NdotH;
	return exp((NdotH2 - 1.0f) / (NdotH2 * a2)) / (PI * a2 * NdotH2 * NdotH2);
}

// [Walter et al. 2007]
float DistributionGGX(float NdotH, float a2)
{
	// �v�Z���������ł���Ȃ�Ƀe�[��������
	float f = NdotH * (NdotH * a2 - NdotH) + 1.f;
	return a2 / (PI * f * f);
}

// [Schlick-Smith 1994]
float GeometrySchlick(float NdotL, float NdotV, float a)
{
	// �ׂ荇��microfacet���m�̍����Ɉ�ѐ����Ȃ����ߐ��m�ł͂Ȃ�
	float k = a * 0.5f;
	float schlickV = NdotV / (NdotV * (1.f - k) + k);
	float schlickL = NdotL / (NdotL * (1.f - k) + k);
	return schlickV * schlickL;
}

// Smith Joint Masking-Shadowing Function
// [Heitz 2014] 2014�N�ȍ~�̎嗬�}�X�L���O�֐�
float GeometrySmithJoint(float NdotL, float NdotV, float a)
{
#if 1
	// ��̑��삪���邽�ߏ�������������萳�m�Ȓl�ɂȂ�
	float a2 = a * a;
	float schlickV = NdotL * sqrt(NdotV * (NdotV - NdotV * a2) + a2);
	float schlickL = NdotV * sqrt(NdotL * (NdotL - NdotL * a2) + a2);
#else
	// ���w�I�ɂ͊Ԉ���Ă��邪�A�������̌v�Z��ߖ�o����
	float schlickV = NdotL * (NdotV * (1.f - a) + a);
	float schlickL = NdotV * (NdotL * (1.f - a) + a);
#endif
	return 0.5f / (schlickV + schlickL);
}

// [Schlick 1994]
float FresnelSchlick(float3 f0, float VdotH)
{
	return f0 + (1.f - f0) * Pow5(1.f - VdotH);
}

float FresnelSchlick(float3 f0, float f90, float VdotH)
{
	return f0 + (f90 - f0) * Pow5(1.f - VdotH);
}

float3 DiffuseLambert(float3 DiffuseColor)
{
	return DiffuseColor / PI;
}

// [EA DICE 2014]
float DiffuseFresnel(float LdotH, float NdotL, float3 NdotV, float roughness)
{
	float energyBias = lerp(0.0f, 0.5f, roughness);
	float energyFactor = lerp(1.0, 1.0 / 1.51, roughness);

	// �������s�ɓ��˂����Ƃ��̊g�U���˗ʂ����߂Ă���
	float fd90 = energyBias + 2.0 * LdotH * LdotH * roughness;

	// �g�U���˗������߂�
	float FL = (1 + (fd90 - 1) * Pow5(1 - NdotL));
	float FV = (1 + (fd90 - 1) * Pow5(1 - NdotV));

	// �ŏI�I�Ȋg�U���˗������߂Ă���BPI�ŏ��Z���Ă���̂͐��K�����s������
	return (FL * FV / energyFactor);
}

float3 SpecularBRDF(float3 specular, float NdotH, float NdotL, float NdotV, float VdotH, Material material)
{
	float a = material.roughness * material.roughness;
	float3 f0 = lerp(0.03f, specular, material.metallic);

	// specular BRDF
	float D = DistributionGGX(NdotH, a * a);
	float G = GeometrySchlick(NdotL, NdotV, a);
	float3 F = FresnelSchlick(f0, VdotH);
	return (D * G * F / PI * NdotV * NdotH);
}

float3 DiffuseBRDF(float3 albedo, float LdotH, float NdotL, float NdotV, Material material)
{
	// diffuse BRDF
	float diffuseFresnel = DiffuseFresnel(LdotH, NdotL, NdotV, material.roughness);
	float3 lambertDiffuse = DiffuseLambert(albedo * NdotL);
	return diffuseFresnel * lambertDiffuse;
}

float3 PBR(Material material, Light light, float3 toEye, float3 normal)
{
	// ���C�g�ւ̃x�N�g���ƃJ�����ւ̃x�N�g���̃n�[�t�x�N�g���v�Z
	float3 h = normalize(light.direction + toEye);

	float NdotV = saturate(dot(normal, toEye));
	float NdotL = saturate(dot(normal, light.direction));
	float NdotH = saturate(dot(normal, h));
	float VdotH = saturate(dot(toEye, h));
	float LdotH = saturate(dot(light.direction, h));

	// BRDF
	float3 specular = SpecularBRDF(material.albedoColor, NdotH, NdotL, NdotV, VdotH, material);	
	float3 diffuse = DiffuseBRDF(material.albedoColor, LdotH, NdotL, NdotV, material);

	return light.color * light.intensity * (diffuse * material.roughness + specular);
}