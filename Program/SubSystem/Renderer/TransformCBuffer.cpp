/**
* @file	   TransformCBuffer.cpp
* @brief
*
* @date	   2022/07/22 2022îNìxèâî≈
*/


#include "TransformCBuffer.h"

void TransformCBuffer::Init()
{
	m_constantBuffer.Create(sizeof(ConstantBufferMatrix));
	m_constantBuffer12.Create(ConstantBufferMatrix());
	m_descriptorHeap.Create(1, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void TransformCBuffer::Bind(const DirectX::XMMATRIX& world)
{
	ConstantBufferMatrix buffer = { DirectX::XMMatrixTranspose(world), m_viewXM, m_projectionXM };

	//m_constantBuffer.Update(buffer);
	m_constantBuffer12.Update(buffer);

	// set buffer
	//m_constantBuffer.VSSet(1);
	//m_constantBuffer.PSSet(1);
	m_descriptorHeap.Set();
}

const DirectX::XMMATRIX& TransformCBuffer::GetProjection() noexcept
{
	return m_projectionXM;
}

void TransformCBuffer::SetProjection(const DirectX::XMMATRIX& projection) noexcept
{
	m_projectionXM = DirectX::XMMatrixTranspose(projection);
}

const DirectX::XMMATRIX& TransformCBuffer::GetView() noexcept
{
	return m_viewXM;
}

void TransformCBuffer::SetView(const DirectX::XMMATRIX& view) noexcept
{
	m_viewXM = DirectX::XMMatrixTranspose(view);
}