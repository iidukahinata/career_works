#include "Light.hlsli"
#include "Core.hlsli"

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
	float4 finalColor = float4(0, 0, 0, 1);
	
	// �T���v���擾
	float4 baseColor = g_texture.Sample(g_sampler, input.tex);
	
	Light light = ToLightFromDirectionalLight(directionalLight);
	float lightPower = saturate(dot(input.normal, light.direction));

	// ���K�������o�[�g�g�U���ˌ�
	float diffuse = lightPower / PI;

	// ���ʔ��ˌ�
	float3 reflection = reflect(light.direction, input.normal);
	lightPower = saturate(dot(reflection, input.toEye));
	lightPower = Pow5(lightPower);
	float3 specular = lightPower;

	// �ŏI�I�Ȍ�
	finalColor.xyz *= light.color * light.intensity * (diffuse + specular);
	finalColor += (ambientColor * baseColor);
	
	PS_OUT output;
	output.color = finalColor;
	output.depth = input.viewPos.z;

	return output;
}