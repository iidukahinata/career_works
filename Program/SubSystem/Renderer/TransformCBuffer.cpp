/**
* @file	   TransformCBuffer.cpp
* @brief
*
* @date	   2022/05/10 2022îNìxèâî≈
* @author  î—íÀózëæ
*/


#include "TransformCBuffer.h"
#include "SubSystem/Tools/Tools.h"


void TransformCBuffer::Init()
{
	constexpr int bufferSize = AdjustToMultiples(sizeof(ConstantBufferMatrix), 16);
	m_constantBuffer.Create(bufferSize);
}

void TransformCBuffer::Bind(
	const DirectX::XMMATRIX& world,
	const Math::Vector4& color /* = Math::Vector4(1, 1, 1, 1) */
)
{
	ConstantBufferMatrix buffer = {
		DirectX::XMMatrixTranspose(world),
		m_viewXM, m_projectionXM, color
	};

	m_constantBuffer.Update(buffer);

	// set buffer
	m_constantBuffer.VSSet(1);
	m_constantBuffer.PSSet(1);
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