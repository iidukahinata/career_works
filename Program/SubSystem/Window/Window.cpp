/**
* @file    Window.cpp
* @brief   �E�B���h�E�Ǘ��N���X
*
* @date	   2022/05/28 2022�N�x����
* @author  �ђ˗z��
*/


#include "Window.h"
#include "Subsystem/Timer/Timer.h"
#include "Subsystem/Log/DebugLog.h"
#include "ThirdParty/imgui/imgui_impl_win32.h"

/** ���̑O���錾���Ȃ��� imgui �̓��͂��g�p�o���Ȃ� */
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/** �E�B���h�E�v���V�[�W�� */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);

	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wparam)
		{
		case VK_ESCAPE:
			int sts = MessageBoxA(hwnd, "�I�����܂���?", "�I���m�F", MB_YESNO);
			if (sts == IDYES) DestroyWindow(hwnd);
			break;
		}
		break;

	case WM_ACTIVATE:
		if (LOWORD(wparam) != WA_INACTIVE) Timer::Get().ResetMeasurement();
		break;

	case WM_EXITSIZEMOVE:
		Timer::Get().ResetMeasurement();
		break;

	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return 0;
}

bool Window::CreateWindowClass(HINSTANCE hInstance, int width, int height, std::string_view title, bool fullScreen) noexcept
{
	// �^�C�g���o�[�Ƌ��E��������E�B���h�E
	unsigned long windowStyles = WS_OVERLAPPEDWINDOW;
	if (fullScreen)
	{
		// �t���X�N���[�����̓^�C�g���o�[������
		windowStyles = WS_CAPTION | WS_SYSMENU | WS_MAXIMIZE;
		m_width = GetSystemMetrics(SM_CXSCREEN);
		m_height = GetSystemMetrics(SM_CYSCREEN);
		m_fullscreen = true;
	}
	else 
	{
		m_width = width;
		m_height = height;
		m_fullscreen = false;
	}

	WNDCLASSEX w = {};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProcedure;
	w.lpszClassName = "windowClass";
	w.hInstance = hInstance;
	if (!RegisterClassEx(&w)) 
	{
		LOG_ERROR("RegisterClassEx �Ɏ��s���܂����B");
		return false;
	}

	m_hWnd = CreateWindow(
		w.lpszClassName,
		title.data(),
		windowStyles,
		CW_USEDEFAULT,		// �E�B���h�E�̍���w���W
		CW_USEDEFAULT,		// �E�B���h�E�̍���x���W
		m_width,
		m_height,
		nullptr,			// �e�E�B���h�E�̃n���h��
		nullptr,			// ���j���[�n���h��
		hInstance,			// �Ăяo���A�v���P�[�V�����n���h��
		nullptr);			// �ǉ��p�����[�^

	if (m_hWnd == nullptr)
	{
		LOG_ERROR("CreateWindow �Ɏ��s���܂����B");
		return false;
	}

	return true;
}

bool Window::Tick()
{
	if (PeekMessage(&m_message, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&m_message);
		DispatchMessage(&m_message);
	}

	return m_message.message != WM_QUIT;
}

HWND Window::GetHandle() const noexcept
{
	return m_hWnd;
}

long Window::GetMessage() const noexcept
{
	return m_message.message;
}

int Window::GetWindowWidth() const noexcept
{
	return m_width;
}

int Window::GetWindowHeight() const noexcept
{
	return m_height;
}

bool Window::IsFullscreen() const noexcept
{
	return m_fullscreen;
}