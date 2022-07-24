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