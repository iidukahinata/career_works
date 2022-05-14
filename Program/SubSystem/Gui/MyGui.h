/**
* @file    MyGui.h
* @brief   gui管理クラス
*
* @date	   2022/04/29 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include <functional>

/**
* デバッグモード時のみ有効。
* リリースモード時は関数内処理が行われないようになっている。
*/
class MyGui
{
private:

	MyGui() = default;
	MyGui(const MyGui&) = default;
	MyGui& operator=(const MyGui&) = default;

public:

	static MyGui& Get() noexcept
	{
		static MyGui instance;
		return instance;
	}

	void Init();
	void Draw();
	void Exit();
	void Clear();

	typedef std::function<void()> Widget;

	/**
	* GUI描画時に処理される処理の追加
	* @param widget [入力] 追加処理する関数を指定。
	*					   null指定を想定していない。
	*/
	void AddWidget(Widget&& widget) noexcept;

private:

	// * imgui用描画 function 関数配列
	std::vector<Widget> m_widgets;
};