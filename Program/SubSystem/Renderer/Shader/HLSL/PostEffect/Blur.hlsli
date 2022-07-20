Texture2D g_texture;
sampler g_sampler;

cbuffer ConstBufferBlur : register(b3)
{
	float4 weights[2];
	float2 screenSize;
};

struct VS_IN {
	float4 pos : POSITION;
	float2 tex : TEXCOORD0;
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float4 tex1 : TEXCOORD1;
    float4 tex2 : TEXCOORD2;
    float4 tex3 : TEXCOORD3;
    float4 tex4 : TEXCOORD4;
    float4 tex5 : TEXCOORD5;
    float4 tex6 : TEXCOORD6;
    float4 tex7 : TEXCOORD7;
    float4 tex8 : TEXCOORD8;
};

struct PS_IN {
    float4 pos : POSITION;
    float4 tex1 : TEXCOORD1;
    float4 tex2 : TEXCOORD2;
    float4 tex3 : TEXCOORD3;
    float4 tex4 : TEXCOORD4;
    float4 tex5 : TEXCOORD5;
    float4 tex6 : TEXCOORD6;
    float4 tex7 : TEXCOORD7;
    float4 tex8 : TEXCOORD8;
};