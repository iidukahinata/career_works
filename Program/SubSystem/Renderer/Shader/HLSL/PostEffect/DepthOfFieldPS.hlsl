Texture2D<float4> g_blurTexture : register(t0);
Texture2D<float> g_depthTexture : register(t1);
sampler g_sampler;

struct PS_IN {
	float4 pos : POSITION;
	float2 tex : TEXCOORD;
};

float4 main(PS_IN input) : SV_TARGET
{
    // 深度値を取得
	float depth = g_depthTexture.Sample(g_sampler, input.tex);

    // 深度値が10以下なら描きこまない    
    //if ((depth - 1.f) > 0)
    {
		float4 finalColor = g_blurTexture.Sample(g_sampler, input.tex);
        
        // 深度値から不透明度を計算する
        // 深度値10からボケが始まり、深度値100で最大のボケ具合になる
		finalColor.xyz = depth;//min(1.0f, (depth - 5.f) / 100.f);
		finalColor.a = 1.f;
        return finalColor;
	}
	return float4(0, 0, 0, 0);
}