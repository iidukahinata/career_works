/**
* @file    D3D12DeviceChild.h
* @brief
*
* @date	   2022/08/01 2022�N�x����
*/
#pragma once


#include "D3D12Helper.h"

enum ShaderType
{
	VertexShader,
	PixelShader,
	GeometryShader,
	HullShader,
	DomainShader,
	Max
};

/**
* D3D12 �e�N���X�̒��ۃN���X
* GraphicsDevive class �̃A�N�Z�X���@�ɕύX���������ꍇ�ł��A
* �h����ɉe�����Ȃ��悤�ɂ��̃N���X���A�N�Z�X������B
* GraphicsDevive class �ɕύX���������ꍇ�͒x���Z�b�g�A�b�v�֐����쐬���đΏ�������̂Ǝv����B
*/
class D3D12DeviceChild
{
public:

	virtual ~D3D12DeviceChild() {}

protected:

	class ID3D12Device* GetDevice() const noexcept;
	class D3D12CommandContext* GetCommandContext() const noexcept;

	class D3D12DescriptorAllocator& GetViewDescriptorAllocator() noexcept;
	class D3D12DescriptorAllocator& GetSamplerDescriptorAllocator() noexcept;
	class D3D12DescriptorAllocator& GetRtvDescriptorAllocator() noexcept;
	class D3D12DescriptorAllocator& GetDsvDescriptorAllocator() noexcept;
	D3D12Map<D3D12_SAMPLER_DESC, class D3D12Sampler*>& GetSamplerMap() noexcept;
};