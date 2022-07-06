/**
* @file    Window.h
* @brief
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


#include <Windows.h>

class Window
{
	Window() = default;
	COPY_PROHIBITED(Window)
public:

	static Window& Get() noexcept
	{
		static Window instance;
		return instance;
	}

	/**
	* 設定された値で Window を作成
	* @param hInstance [入力] 実行時のインスタンスハンドルを指定する必要があります。
	* @param width [入力] ０以下の値を指定しないでください。
	* @param height [入力] ０以下の値を指定しないでください。
	* @param title [入力] 生成する Window のタイトルバーに出力する文字列。nullは考慮していない。
	* @param fullScreen [入力] trueが指定された時は hInstance 以外の引数値の意味はなくなります。
	*/
	bool CreateWindowClass(HINSTANCE hInstance, int width, int height, String_View title, bool fullScreen) noexcept;

	/**
	* window message から window 状態を調べる
	* @return false の場合は window の終了合図
	*/
	bool Tick();

	/** 生成された Window 識別子を返します。 */
	HWND GetHandle() const noexcept;

	/** 最後に更新された時の細かな window 状態を返します。 */
	long GetMessage() const noexcept;

	int	 GetWindowWidth() const noexcept;
	int	 GetWindowHeight() const noexcept;
	bool IsFullscreen() const noexcept;

private:

	// * 生成した window 識別子
	HWND m_hWnd;

	//*  window 状態を外部から取得するための変数
	MSG m_message;

	// * window size
	int m_width;
	int m_height;
	bool m_fullscreen;
};