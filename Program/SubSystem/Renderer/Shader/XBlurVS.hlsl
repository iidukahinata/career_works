#include "Core.hlsli"
#include "Blur.hlsli"

VS_OUT main(VS_IN input)
{
    VS_OUT output;

    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

    // テクセルをずらし周辺からサンプリングするためのUV値
    output.tex1.xy = float2( 1.f / screenSize.x, 0.f);
    output.tex2.xy = float2( 3.f / screenSize.x, 0.f);
    output.tex3.xy = float2( 5.f / screenSize.x, 0.f);
    output.tex4.xy = float2( 7.f / screenSize.x, 0.f);
    output.tex5.xy = float2( 9.f / screenSize.x, 0.f);
    output.tex6.xy = float2(11.f / screenSize.x, 0.f);
    output.tex7.xy = float2(13.f / screenSize.x, 0.f);
	output.tex8.xy = float2(15.f / screenSize.x, 0.f);

    // 反対方向のUV値を求める
    output.tex1.zw = output.tex1.xy * -1.f;
    output.tex2.zw = output.tex2.xy * -1.f;
    output.tex3.zw = output.tex3.xy * -1.f;
    output.tex4.zw = output.tex4.xy * -1.f;
    output.tex5.zw = output.tex5.xy * -1.f;
    output.tex6.zw = output.tex6.xy * -1.f;
    output.tex7.zw = output.tex7.xy * -1.f;
    output.tex8.zw = output.tex8.xy * -1.f;

    // 実際のUV座標に変換
    output.tex1 += float4(input.tex, input.tex);
    output.tex2 += float4(input.tex, input.tex);
    output.tex3 += float4(input.tex, input.tex);
    output.tex4 += float4(input.tex, input.tex);
    output.tex5 += float4(input.tex, input.tex);
    output.tex6 += float4(input.tex, input.tex);
    output.tex7 += float4(input.tex, input.tex);
    output.tex8 += float4(input.tex, input.tex);

    return output;
}