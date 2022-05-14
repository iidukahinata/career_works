TextureCube<float4> g_cubeMap;
SamplerState g_sampler;

struct PS_IN {
	float4 pos : SV_POSITION;
	float4 tex : TEXCOORD1;
	float4 viewPos : TEXCOORD3;
};

struct PS_OUT
{
	float4 color : SV_TARGET0;
	float depth : SV_TARGET1;
};

PS_OUT main(PS_IN input)
{
	PS_OUT output;
	
	output.color = g_cubeMap.Sample(g_sampler, input.tex.xyz);
	output.depth = input.viewPos.z;
	
	return output;
}