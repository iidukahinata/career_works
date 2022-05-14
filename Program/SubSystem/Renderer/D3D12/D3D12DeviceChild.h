/**
* @file    D3D12DeviceChild.h
* @brief
*
* @date	   2022/05/13 2022�N�x����
* @author  �ђ˗z��
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

	D3D12DeviceChild();
	virtual ~D3D12DeviceChild() {}

	class D3D12GrahicsDevice* GetGraphicsDevice() const noexcept;

private:

	class D3D12GrahicsDevice* m_grahicsDevice = nullptr;
};