#define MAX_LIGHT_COUNT 256

Texture3D<uint2> g_lightDataTex : register(t10);
Texture1D<min16int> g_lightIndicesTex : register(t11);

struct Light
{
	float3 direction;
	float3 color;
	float intensity;
};

struct DirectionalLight
{
	float4 direction;
	float4 color; // w値 intensity
};

struct PointLight
{
	float4 position;
	float4 color;
	float4 intensity; // x値 intensity : y値 influenceRange
};

struct SpotLight
{
	float4 position;
	float4 direction;
	float4 color;
	float4 intensity; // x値 intensity : y値 influenceRange : z値 angle
};

cbuffer ConstBufferLight : register(b2)
{
	float4 gEyePos;
	float4 ambientColor;
	DirectionalLight directionalLight;
	PointLight pointLights[MAX_LIGHT_COUNT];
	SpotLight spotLights[MAX_LIGHT_COUNT];
	
	float2 lightCount; // x値 pointLight : y値 sptLight
	
	float4 invScale;
	float4 bias;
};

cbuffer ConstBufferLightList
{
	min16int lightIndices[0x1000];
}

Light ToLightFromDirectionalLight(DirectionalLight directionalLight)
{
	Light light;
	light.direction = normalize(-directionalLight.direction).xyz;
	light.color = directionalLight.color.xyz;
	light.intensity = directionalLight.color.w;
	return light;
}

Light ToLightFromPointLight(PointLight pointLight, float4 pos)
{
	Light light;
	light.direction = normalize(pos - pointLight.position);
	light.color = pointLight.color.xyz;
	light.intensity = pointLight.intensity.x;

	// 距離による影響力を計算
	float distance = length(pos - pointLight.position);
	float att = saturate(1.f - distance / pointLight.intensity.y);
	att *= att; // 影響力を滑らかにする

	light.intensity *= att;
	return light;
}

Light ToLightFromSpotLight(SpotLight spotLight, float4 pos)
{
	Light light;
	light.direction = normalize(pos - spotLight.position);
	light.color = spotLight.color;
	light.intensity = spotLight.intensity.x;

	// 距離による影響力を計算
	float distance = length(pos - spotLight.position);
	float disAtt = saturate(1.f - distance / spotLight.intensity.y);
	disAtt *= disAtt; // 影響力を滑らかにする

	// 角度による影響力を計算
	float angle = dot(light.direction, spotLight.direction.xyz);
	angle = abs(acos(angle));
	float angleAtt = saturate(1.f - angle / spotLight.intensity.z);
	angleAtt = pow(angleAtt, 0.5); // 影響力を滑らかにする

	light.intensity *= angleAtt * disAtt;
	return light;
}