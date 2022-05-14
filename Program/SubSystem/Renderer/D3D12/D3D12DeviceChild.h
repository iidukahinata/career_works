/**
* @file    D3D12DeviceChild.h
* @brief
*
* @date	   2022/05/13 2022年度初版
* @author  飯塚陽太
*/
#pragma once


/**
* D3D12 各クラスの抽象クラス
* GraphicsDevive class のアクセス方法に変更があった場合でも、
* 派生先に影響がないようにこのクラスよりアクセスさせる。
* GraphicsDevive class に変更があった場合は遅延セットアップ関数を作成して対処するものと思われる。
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