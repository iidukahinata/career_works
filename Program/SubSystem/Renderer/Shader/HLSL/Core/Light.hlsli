#define MAXLIGHTCOUNT 256

Texture3D<uint> g_lightDataTex : register(t10);

struct Light 
{
	float3 direction;
	float3 color;
	float intensity;
};

struct DirectionalLight
{
	float4 direction;
	float4 color; // w�l intensity
};

struct PointLight
{
	float4 position;
	float4 color;
	float4 intensity; // x�l intensity : y�l influenceRange
};

struct SpotLight
{
	float4 position;
	float4 direction;
	float4 color;
	float4 intensity; // x�l intensity : y�l influenceRange : z�l angle
};

cbuffer ConstBufferLight : register(b2)
{
	float4 gEyePos;
	float4 ambientColor;
	DirectionalLight directionalLight;
	PointLight pointLights[MAXLIGHTCOUNT];
	SpotLight spotLights[MAXLIGHTCOUNT];
	
	float2 lightCount; // x�l pointLight : y�l sptLight
	
	float4 invScale;
	float4 bias;
};

cbuffer ConstBufferLightList : register(b3)
{	
	min16int lightIndices[0x1000];
};

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
	light.color = pointLight.color.xyz;
	light.intensity = pointLight.intensity.x;
	light.direction = normalize(pos - pointLight.position).xyz;

	// �����ɂ��e���͂��v�Z
	float distance = length(pos - pointLight.position);
	float att = saturate(1.f - distance / pointLight.intensity.y);
	att *= att; // �e���͂����炩�ɂ���

	light.intensity *= att;
	return light;
}

Light ToLightFromSpotLight(SpotLight spotLight, float4 pos)
{
	Light light;
	light.color = spotLight.color.xyz;
	light.intensity = spotLight.intensity.x;
	light.direction = normalize(pos - spotLight.position).xyz;

	// �����ɂ��e���͂��v�Z
	float distance = length(pos - spotLight.position);
	float disAtt = saturate(1.f - distance / spotLight.intensity.y);
	disAtt *= disAtt; // �e���͂����炩�ɂ���

	// �p�x�ɂ��e���͂��v�Z
	float angle = dot(light.direction, spotLight.direction.xyz);
	angle = abs(acos(angle));
	float angleAtt = saturate(1.f - angle / spotLight.intensity.z);
	angleAtt = pow(angleAtt, 0.5); // �e���͂����炩�ɂ���

	light.intensity *= angleAtt * disAtt;
	return light;
}