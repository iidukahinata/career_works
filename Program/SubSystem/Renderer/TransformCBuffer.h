/**
* @file	   TransformCBuffer.h
* @brief
*
* @date	   2022/07/27 2022年度初版
*/
#pragma once


#include "SubSystem/Renderer/D3D12/D3D12ConstantBuffer.h"
#include "SubSystem/Renderer/D3D12/D3D12DescriptorHeap.h"

class TransformCBuffer
{
	TransformCBuffer() = default;
	COPY_PROHIBITED(TransformCBuffer)
public:

	static TransformCBuffer& Get() noexcept
	{
		static TransformCBuffer instance;
		return instance;
	}

	void Init() noexcept;

	/* デバイス設定を変更します。*/
	void Bind(const DirectX::XMMATRIX& world) noexcept;

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

	D3D12DescriptorHeap m_descriptHeap;
	D3D12ConstantBuffer m_constantBuffer;
};