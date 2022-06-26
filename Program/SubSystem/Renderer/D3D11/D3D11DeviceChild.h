/**
* @file    D3D11DeviceChild.h
* @brief
*
* @date	   2022/06/25 2022年度初版
*/
#pragma once


#include "D3D11GrahicsDevice.h"

/**
* D3D11 各クラスの抽象クラス
* GraphicsDevive クラスと 各派先クラスを分離させるために作成。
*/
class D3D11DeviceChild
{
public:

	D3D11DeviceChild() 
	{
		m_d3dDevice = D3D11GrahicsDevice::Get().GetDevice();
		m_d3dContext = D3D11GrahicsDevice::Get().GetContext();
	}

	virtual ~D3D11DeviceChild() 
	{

	}
	
	ID3D11Device* GetDevice() const
	{
		return m_d3dDevice;
	}

	ID3D11DeviceContext* GetContext() const
	{
	 	return m_d3dContext;
	}

private:

	ID3D11Device* m_d3dDevice;
	ID3D11DeviceContext* m_d3dContext;
};