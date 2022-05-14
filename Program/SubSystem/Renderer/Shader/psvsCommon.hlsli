

/*
* コンスタントバッファー
*/
cbuffer ConstBufferMatrix : register(b1)
{
	matrix world;
	matrix view;
	matrix projection;
	float4 color;
};