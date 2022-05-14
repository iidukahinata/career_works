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

	// ���K�������o�[�g�g�U���ˌ�
	float diffuse = directionalLight.color * lightPower / PI;

	// ���ʔ��˂̋���
	float3 reflection = reflect(lightDirection, input.normal);
	lightPower = saturate(dot(reflection, input.toEye));
	lightPower = pow(lightPower, 5.0f);

	// ���ʔ��ˌ�
	float3 specular = directionalLight.color * lightPower;

	// �ŏI�I�Ȍ�
	float3 light = diffuse + specular;
	light += 0.4f;

	float4 finalColor = g_texture.Sample(g_sampler, input.tex);
	finalColor.xyz *= light;

	PS_OUT output;
	output.color = finalColor;
	output.depth = input.viewPos.z;

	return output;
}