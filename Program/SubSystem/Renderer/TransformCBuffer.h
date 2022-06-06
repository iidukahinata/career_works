/**
* @file	   TransformCBuffer.h
* @brief
*
* @date	   2022/06/06 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include "SubSystem/Renderer/D3D11/D3D11ConstantBuffer.h"

class TransformCBuffer
{
private:

	TransformCBuffer() = default;
	TransformCBuffer(const TransformCBuffer&) = default;
	TransformCBuffer& operator=(const TransformCBuffer&) = default;

public:

	static TransformCBuffer& Get() noexcept
	{
		static TransformCBuffer instance;
		return instance;
	}

	void Init();

	/* デバイス設定を変更します。*/
	void Bind(const DirectX::XMMATRIX& world);

	const DirectX::XMMATRIX& GetProjection() noexcept;
	void SetProjection(const DirectX::XMMATRIX& projection) noexcept;

	const DirectX::XMMATRIX& GetView() noexcept;
	void SetView(const DirectX::XMMATRIX& view) noexcept;

private:

	DirectX::XMMATRIX m_viewXM;
	DirectX::XMMATRIX m_projectionXM;

	struct ConstantBufferMatrix
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

	D3D11ConstantBuffer<ConstantBufferMatrix> m_constantBuffer;
};