/**
* @file    D3D12DeviceChild.h
* @brief
*
* @date	   2022/07/22 2022�N�x����
*/
#pragma once


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

	class ID3D12Device* GetDevice() const noexcept;
	class D3D12CommandContext* GetContext() const noexcept;
};