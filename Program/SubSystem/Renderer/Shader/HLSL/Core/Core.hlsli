#define PI 3.141592654

cbuffer ConstBufferMatrix : register(b0)
{
	matrix gWorld;
	matrix gView;
	matrix gProjection;
};

float Pow2(float x)
{
	return x * x;
}

float Pow3(float x)
{
	return x * x * x;
}

float Pow4(float x)
{
	return x * x * x * x;
}

float Pow5(float x)
{
	return x * x * x * x * x;
}