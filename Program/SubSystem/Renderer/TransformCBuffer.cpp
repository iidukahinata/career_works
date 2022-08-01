/**
* @file	   TransformCBuffer.cpp
* @brief
*
* @date	   2022/07/27 2022îNìxèâî≈
*/


#include "TransformCBuffer.h"

void TransformCBuffer::Init() noexcept
{
	m_descriptHeap.Create(1, DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	m_constantBuffer.Create(sizeof(ConstantBufferMatrix));
	m_descriptHeap.RegisterConstantBufferView(m_constantBuffer.GetDesc());
}

void TransformCBuffer::Bind(const DirectX::XMMATRIX& world) noexcept
{
	static_cast<ConstantBufferMatrix*>(m_constantBuffer.GetCPUData())->world = DirectX::XMMatrixTranspose(world);

	// set buffer
	m_descriptHeap.Set();
	m_descriptHeap.SetGraphicsRootTable(1);
}

const DirectX::XMMATRIX& TransformCBuffer::GetProjection() noexcept
{
	return m_projectionXM;
}

void TransformCBuffer::SetProjection(const DirectX::XMMATRIX& projection) noexcept
{
	m_projectionXM = DirectX::XMMatrixTranspose(projection);
	static_cast<ConstantBufferMatrix*>(m_constantBuffer.GetCPUData())->projection = m_projectionXM;
}

const DirectX::XMMATRIX& TransformCBuffer::GetView() noexcept
{
	return m_viewXM;
}

void TransformCBuffer::SetView(const DirectX::XMMATRIX& view) noexcept
{
	m_viewXM = DirectX::XMMatrixTranspose(view);
	static_cast<ConstantBufferMatrix*>(m_constantBuffer.GetCPUData())->view = m_viewXM;
}