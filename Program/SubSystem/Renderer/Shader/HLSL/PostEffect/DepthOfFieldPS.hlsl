Texture2D<float4> g_blurTexture : register(t0);
Texture2D<float> g_depthTexture : register(t1);
sampler g_sampler;

struct PS_IN {
	float4 pos : POSITION;
	float2 tex : TEXCOORD;
};

float4 main(PS_IN input) : SV_TARGET
{
    // �[�x�l���擾
	float depth = g_depthTexture.Sample(g_sampler, input.tex);

    // �[�x�l��10�ȉ��Ȃ�`�����܂Ȃ�    
    //if ((depth - 1.f) > 0)
    {
		float4 finalColor = g_blurTexture.Sample(g_sampler, input.tex);
        
        // �[�x�l����s�����x���v�Z����
        // �[�x�l10����{�P���n�܂�A�[�x�l100�ōő�̃{�P��ɂȂ�
		finalColor.xyz = depth;//min(1.0f, (depth - 5.f) / 100.f);
		finalColor.a = 1.f;
        return finalColor;
	}
	return float4(0, 0, 0, 0);
}