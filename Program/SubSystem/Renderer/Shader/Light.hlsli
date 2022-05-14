#define MAXLIGHTCOUNT 64

struct Light 
{
	float3 direction;
	float3 color;
	float intensity;
};

struct DirectionalLight
{
	float4 direction;
	float4 color;
	float4 intensity; // x’l‚Ì‚Ý—LŒø
};

struct PointLight
{
	float4 position;
	float4 color;
	float4 intensity; // x’l intensity : y’l influenceRange
};

struct SpotLight
{
	float4 position;
	float4 direction;
	float4 color;
	float4 intensity; // x’l intensity : y’l influenceRange : z’l angle
};

cbuffer ConstBufferLight : register(b2)
{
	float4 gEyePos;
	float4 ambientColor;
	DirectionalLight directionalLight;
	PointLight pointLights[MAXLIGHTCOUNT];
	SpotLight spotLights[MAXLIGHTCOUNT];
	
	float2 lightCount; // x’l pointLight : y’l sptLight
};


Light ToLightFromDirectionalLight(DirectionalLight directionalLight)
{
	Light light;
	light.direction = normalize(-directionalLight.direction);
	light.color = directionalLight.color;
	light.intensity = directionalLight.intensity.x;
	return light;
}

Light ToLightFromPointLight(PointLight pointLight, float4 pos)
{
	Light light;
	light.color = pointLight.color;
	light.intensity = pointLight.intensity.x;
	light.direction = normalize(pos - pointLight.position);

	// ‹——£‚É‚æ‚é‰e‹¿—Í‚ðŒvŽZ
	float distance = length(pos - pointLight.position);
	float att = saturate(1.f - distance / pointLight.intensity.y);
	att *= att; // ‰e‹¿—Í‚ðŠŠ‚ç‚©‚É‚·‚é

	light.intensity *= att;
	return light;
}

Light ToLightFromSpotLight(SpotLight spotLight, float4 pos)
{
	Light light;
	light.color = spotLight.color;
	light.intensity = spotLight.intensity.x;
	light.direction = normalize(pos - spotLight.position);

	// ‹——£‚É‚æ‚é‰e‹¿—Í‚ðŒvŽZ
	float distance = length(pos - spotLight.position);
	float disAtt = saturate(1.f - distance / spotLight.intensity.y);
	disAtt *= disAtt; // ‰e‹¿—Í‚ðŠŠ‚ç‚©‚É‚·‚é

	// Šp“x‚É‚æ‚é‰e‹¿—Í‚ðŒvŽZ
	float angle = dot(light.direction, spotLight.direction.xyz);
	angle = abs(acos(angle));
	float angleAtt = saturate(1.f - angle / spotLight.intensity.z);
	angleAtt = pow(angleAtt, 0.5); // ‰e‹¿—Í‚ðŠŠ‚ç‚©‚É‚·‚é

	light.intensity *= angleAtt * disAtt;
	return light;
}