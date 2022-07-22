/**
* @file    D3D11DeviceChild.h
* @brief
*
* @date	   2022/06/25 2022�N�x����
*/
#pragma once


#include "D3D11GrahicsDevice.h"

/**
* D3D11 �e�N���X�̒��ۃN���X
* GraphicsDevive �N���X�� �e�h��N���X�𕪗������邽�߂ɍ쐬�B
*/
class D3D11DeviceChild
{
public:

	virtual ~D3D11DeviceChild() {}
	
	ID3D11Device* GetDevice() const
	{
		return D3D11GraphicsDevice::Get().GetDevice();
	}

	ID3D11DeviceContext* GetContext() const
	{
	 	return D3D11GraphicsDevice::Get().GetContext();
	}
};