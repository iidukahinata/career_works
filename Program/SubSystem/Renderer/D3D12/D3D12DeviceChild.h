/**
* @file    D3D12DeviceChild.h
* @brief
*
* @date	   2022/07/22 2022年度初版
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

	virtual ~D3D12DeviceChild() {}

	class ID3D12Device* GetDevice() const noexcept;
	class D3D12CommandContext* GetContext() const noexcept;
};