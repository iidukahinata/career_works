/**
* @file    MyGui.h
* @brief   gui管理クラス
*
* @date	   2022/07/26 2022年度初版
*/
#pragma once


#include "SubSystem/Renderer/D3D12/D3D12DescriptorHeap.h"

class Widget;

class EditerSystem
{
	EditerSystem() = default;
	COPY_PROHIBITED(EditerSystem);
public:

	static EditerSystem& Get() noexcept
	{
		static EditerSystem instance;
		return instance;
	}

	void Initialize() noexcept;
	void BegineFrame() noexcept;
	void Render() noexcept;
	void Exit() noexcept;

	/** Widget メソッド */
	void RegisterWidget(Widget* widget) noexcept;
	void RemoveWidget(Widget* widget) noexcept;

private:

	// * Gui 用描画クラス配列
	Set<Widget*> m_widgets;

	// * renderCommand が処理されたかどうかを判別
	bool isRender = true;

	D3D12DescriptorHeap m_descriptHeap;
};