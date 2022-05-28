/**
* @file    Window.h
* @brief   �E�B���h�E�Ǘ��N���X
*
* @date	   2022/05/06 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include <Windows.h>
#include <string_view>

class Window
{
private:

	Window() = default;
	Window(const Window&) = default;
	Window& operator=(const Window&) = default;

public:

	static Window& Get() noexcept
	{
		static Window instance;
		return instance;
	}

	/**
	* �ݒ肳�ꂽ�l�� Window ���쐬
	* @param hInstance [����] ���s���̃C���X�^���X�n���h�����w�肷��K�v������܂��B
	* @param width [����] �O�ȉ��̒l���w�肵�Ȃ��ł��������B
	* @param height [����] �O�ȉ��̒l���w�肵�Ȃ��ł��������B
	* @param title [����] �������� Window �̃^�C�g���o�[�ɏo�͂��镶����Bnull�͍l�����Ă��Ȃ��B
	* @param fullScreen [����] true���w�肳�ꂽ���� hInstance �ȊO�̈����l�̈Ӗ��͂Ȃ��Ȃ�܂��B
	*/
	bool CreateWindowClass(HINSTANCE hInstance, int width, int height, std::string_view title, bool fullScreen) noexcept;

	/**
	* window message ���� window ��Ԃ𒲂ׂ�
	* @return false �̏ꍇ�� window �̏I�����}
	*/
	bool Tick();

	/** �������ꂽ Window ���ʎq��Ԃ��܂��B */
	HWND GetHandle() const noexcept;

	/** �Ō�ɍX�V���ꂽ���ׂ̍��� window ��Ԃ�Ԃ��܂��B */
	long GetMessage() const noexcept;

	int	 GetWindowWidth() const noexcept;
	int	 GetWindowHeight() const noexcept;
	bool IsFullscreen() const noexcept;

private:

	/** �������� window ���ʎq */
	HWND m_hWnd;

	/** window ��Ԃ��O������擾���邽�߂̕ϐ� */
	MSG m_message;

	/** window size */
	int m_width;
	int m_height;
	bool m_fullscreen;
};