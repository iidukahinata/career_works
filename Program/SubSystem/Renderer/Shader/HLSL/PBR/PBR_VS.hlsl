#include "../Core/Core.hlsli"
#include "../Core/Light.hlsli"

struct VS_IN {
    float4 pos : POSITION;
    float3 normal : NORMAL;
    float3 tangent  : TANGENT;
    float3 biNormal : BINORMAL;
    float2 tex : TEXCOORD0;
};

struct VS_OUT {
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float3 tangent  : TANGENT;
	float3 biNormal : BINORMAL;
	float2 tex : TEXCOORD0;    
	float4 worldPos : TEXCOORD1;
	float4 viewPos : TEXCOORD2;
	float3 toEye : TEXCOORD3;
};

VS_OUT main(VS_IN input)
{
    VS_OUT output;

    // 各空間の座標取得
	output.worldPos = mul(input.pos, world);
	output.viewPos = mul(output.worldPos, view);
	output.pos = mul(output.viewPos, projection);
    
	output.normal = normalize(mul(world, float4(input.normal, 0.f)));
	output.tangent = normalize(mul(world, float4(input.tangent, 0.f)));
	output.biNormal = normalize(mul(world, float4(input.biNormal, 0.f)));

    output.tex = input.tex;
		
	// カメラ方向へのベクトル計算
	output.toEye = normalize(gEyePos - output.worldPos);

	return output;
}