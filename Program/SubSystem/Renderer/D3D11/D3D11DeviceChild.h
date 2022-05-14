/**
* @file    D3D11DeviceChild.h
* @brief
*
* @date	   2022/04/29 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include "D3D11GrahicsDevice.h"

/**
* D3D11 各クラスの抽象クラス
* GraphicsDevive class のアクセス方法に変更があった場合でも、
* 派生先に影響がないようにこのクラスよりアクセスさせる。
* GraphicsDevive class に変更があった場合は遅延セットアップ関数を作成して対処するものと思われる。
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