/**
* @file    D3D11DeviceChild.h
* @brief
*
* @date	   2022/04/29 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include "D3D11GrahicsDevice.h"

/**
* D3D11 �e�N���X�̒��ۃN���X
* GraphicsDevive class �̃A�N�Z�X���@�ɕύX���������ꍇ�ł��A
* �h����ɉe�����Ȃ��悤�ɂ��̃N���X���A�N�Z�X������B
* GraphicsDevive class �ɕύX���������ꍇ�͒x���Z�b�g�A�b�v�֐����쐬���đΏ�������̂Ǝv����B
*/
class D3D11DeviceChild
{
public:

	D3D11DeviceChild() 
	{
		m_grahicsDevice = &D3D11GrahicsDevice::Get();
	}

	virtual ~D3D11DeviceChild() 
	{

	}

	D3D11GrahicsDevice* GetGraphicsDevice() const noexcept
	{
		return m_grahicsDevice;
	}

private:

	D3D11GrahicsDevice* m_grahicsDevice = nullptr;
};