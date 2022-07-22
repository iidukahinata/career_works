/**
* @file    MyGui.h
* @brief   gui管理クラス
*
* @date	   2022/07/19 2022年度初版
*/
#pragma once


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
	void Draw() noexcept;
	void Exit() noexcept;

	/** Widget メソッド */
	void RegisterWidget(Widget* widget) noexcept;
	void RemoveWidget(Widget* widget) noexcept;

private:

	// * Gui 用描画クラス配列
	Set<Widget*> m_widgets;
};