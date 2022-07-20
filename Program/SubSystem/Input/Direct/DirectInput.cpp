/**
 * @file	DirectInput.cpp
 * @brief
 *
 * @date	2022/07/19 2022�N�x����
 */


#include "DirectInput.h"
#include "SubSystem/Window/Window.h"

DirectInput::DirectInput()
{
	m_previousKeyState.fill(false);

	m_job.SetFunction([this](double) { Update(); }, FunctionType::Update);
	m_job.RegisterToJobSystem();
}

bool DirectInput::Initialize()
{
	auto width = Window::Get().GetWindowWidth();
	auto height = Window::Get().GetWindowHeight();
	auto hwnd = Window::Get().GetHandle();
	auto hInstance = Window::Get().GetHInstance();

	HRESULT	hr;
	hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, nullptr);
	if (FAILED(hr)) {
		return false;
	}

	// �L�[�{�[�h�f�o�C�X����
	m_directInput->CreateDevice(GUID_SysKeyboard, &m_directKeyboard, nullptr);
	if (FAILED(hr)) {
		return false;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	hr = m_directKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) {
		return false;
	}

	// �������x���̐ݒ�
	hr = m_directKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) {
		return false;
	}

	// �}�E�X�f�o�C�X����
	m_directInput->CreateDevice(GUID_SysMouse, &m_directMouse, nullptr);
	if (FAILED(hr)) {
		return false;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	hr = m_directMouse->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(hr)) {
		return false;
	}

	// �������x���̐ݒ�
	hr = m_directMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) {
		return false;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;							// ���Βl���[�h
	m_directMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);	// �����[�h�̐ݒ�

	DIPROPRANGE diprg;
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwObj = DIJOFS_X;
	diprg.diph.dwHow = DIPH_BYOFFSET;
	diprg.lMin = 0;
	diprg.lMax = width - 1;

	m_directMouse->SetProperty(DIPROP_RANGE, &diprg.diph);	// �w�����͈̔͂��w��
	diprg.diph.dwObj = DIJOFS_Y;
	diprg.diph.dwHow = DIPH_BYOFFSET;
	diprg.lMin = 0;
	diprg.lMax = height - 1;
	m_directMouse->SetProperty(DIPROP_RANGE, &diprg.diph);	// �x�����͈̔͂��w��

	return true;
}

void DirectInput::Shutdown()
{
	m_job.UnRegisterFromJobSystem();
}

void DirectInput::Update() noexcept
{
	// key ���̎擾�B
	GetKeyBuffer();
	GetMouseBuffer();

	// DirectInput �f�[�^��Event�����o����悤�ɕϊ���������B
	const auto oldpreviousKeyState = m_previousKeyState;
	ConvertMyInputData();

	// �e Event �𒲂ׂ�B
	for (int i = 0; i < m_previousKeyState.max_size(); ++i)
	{
		if (m_previousKeyState[i] && !oldpreviousKeyState[i])
		{
			PressKey(static_cast<Button::KeyAndMouse>(i));
		}
		else if (!m_previousKeyState[i] && oldpreviousKeyState[i])
		{
			ReleaseKey(static_cast<Button::KeyAndMouse>(i));
		}
	}
}

bool DirectInput::GetKeyBuffer() noexcept
{
	HRESULT	hr;

	// �f�o�C�X�̔F��
	hr = m_directKeyboard->Acquire();
	hr = m_directKeyboard->GetDeviceState(sizeof(m_keybuffer), (LPVOID)&m_keybuffer);
	if (hr == DIERR_INPUTLOST)
	{
		hr = m_directKeyboard->Acquire();
		return false;
	}

	return true;
}

bool DirectInput::GetMouseBuffer() noexcept
{
	HRESULT	hr;
	DIMOUSESTATE2 mouseStateOld = m_mouseState;

	// �f�o�C�X�̔F��
	hr = m_directMouse->Acquire();
	hr = m_directMouse->GetDeviceState(sizeof(m_mouseState), &m_mouseState);
	if (hr == DIERR_INPUTLOST)
	{
		hr = m_directMouse->Acquire();
		return false;
	}

	return true;
}

void DirectInput::ConvertMyInputData() noexcept
{
	// MOUSE
	m_previousKeyState[Button::Lbutton] = m_mouseState.rgbButtons[0] & 0x80;
	m_previousKeyState[Button::Rbutton] = m_mouseState.rgbButtons[1] & 0x80;
	m_previousKeyState[Button::Mbutton] = m_mouseState.rgbButtons[2] & 0x80;

	// KEY BOARD
	m_previousKeyState[Button::Escape] = m_keybuffer[DIK_ESCAPE] & 0x80;
	m_previousKeyState[Button::Back] = m_keybuffer[DIK_BACK] & 0x80;
	m_previousKeyState[Button::Tab] = m_keybuffer[DIK_TAB] & 0x80;
	m_previousKeyState[Button::A] = m_keybuffer[DIK_A] & 0x80;
	m_previousKeyState[Button::B] = m_keybuffer[DIK_B] & 0x80;
	m_previousKeyState[Button::C] = m_keybuffer[DIK_C] & 0x80;
	m_previousKeyState[Button::D] = m_keybuffer[DIK_D] & 0x80;
	m_previousKeyState[Button::E] = m_keybuffer[DIK_E] & 0x80;
	m_previousKeyState[Button::F] = m_keybuffer[DIK_F] & 0x80;
	m_previousKeyState[Button::G] = m_keybuffer[DIK_G] & 0x80;
	m_previousKeyState[Button::H] = m_keybuffer[DIK_H] & 0x80;
	m_previousKeyState[Button::I] = m_keybuffer[DIK_I] & 0x80;
	m_previousKeyState[Button::J] = m_keybuffer[DIK_J] & 0x80;
	m_previousKeyState[Button::K] = m_keybuffer[DIK_K] & 0x80;
	m_previousKeyState[Button::L] = m_keybuffer[DIK_L] & 0x80;
	m_previousKeyState[Button::N] = m_keybuffer[DIK_N] & 0x80;
	m_previousKeyState[Button::M] = m_keybuffer[DIK_M] & 0x80;
	m_previousKeyState[Button::O] = m_keybuffer[DIK_O] & 0x80;
	m_previousKeyState[Button::P] = m_keybuffer[DIK_P] & 0x80;
	m_previousKeyState[Button::Q] = m_keybuffer[DIK_Q] & 0x80;
	m_previousKeyState[Button::R] = m_keybuffer[DIK_R] & 0x80;
	m_previousKeyState[Button::S] = m_keybuffer[DIK_S] & 0x80;
	m_previousKeyState[Button::T] = m_keybuffer[DIK_T] & 0x80;
	m_previousKeyState[Button::U] = m_keybuffer[DIK_U] & 0x80;
	m_previousKeyState[Button::V] = m_keybuffer[DIK_V] & 0x80;
	m_previousKeyState[Button::W] = m_keybuffer[DIK_W] & 0x80;
	m_previousKeyState[Button::X] = m_keybuffer[DIK_X] & 0x80;
	m_previousKeyState[Button::Y] = m_keybuffer[DIK_Y] & 0x80;
	m_previousKeyState[Button::Z] = m_keybuffer[DIK_Z] & 0x80;
	m_previousKeyState[Button::Return] = m_keybuffer[DIK_RETURN] & 0x80;
	m_previousKeyState[Button::Lcontrol] = m_keybuffer[DIK_LCONTROL] & 0x80;
	m_previousKeyState[Button::Rcontrol] = m_keybuffer[DIK_RCONTROL] & 0x80;
	m_previousKeyState[Button::Lshift] = m_keybuffer[DIK_LSHIFT] & 0x80;
	m_previousKeyState[Button::Rshift] = m_keybuffer[DIK_RSHIFT] & 0x80;
	m_previousKeyState[Button::Lmenu] = m_keybuffer[DIK_LMENU] & 0x80;
	m_previousKeyState[Button::Rmenu] = m_keybuffer[DIK_RMENU] & 0x80;
	m_previousKeyState[Button::Space] = m_keybuffer[DIK_SPACE] & 0x80;
	m_previousKeyState[Button::F1] = m_keybuffer[DIK_F1] & 0x80;
	m_previousKeyState[Button::F2] = m_keybuffer[DIK_F2] & 0x80;
	m_previousKeyState[Button::F3] = m_keybuffer[DIK_F3] & 0x80;
	m_previousKeyState[Button::F4] = m_keybuffer[DIK_F4] & 0x80;
	m_previousKeyState[Button::F5] = m_keybuffer[DIK_F5] & 0x80;
	m_previousKeyState[Button::F6] = m_keybuffer[DIK_F6] & 0x80;
	m_previousKeyState[Button::F7] = m_keybuffer[DIK_F7] & 0x80;
	m_previousKeyState[Button::F8] = m_keybuffer[DIK_F8] & 0x80;
	m_previousKeyState[Button::F9] = m_keybuffer[DIK_F9] & 0x80;
	m_previousKeyState[Button::F10] = m_keybuffer[DIK_F10] & 0x80;
	m_previousKeyState[Button::F11] = m_keybuffer[DIK_F11] & 0x80;
	m_previousKeyState[Button::F12] = m_keybuffer[DIK_F12] & 0x80;
	m_previousKeyState[Button::Pause] = m_keybuffer[DIK_PAUSE] & 0x80;
	m_previousKeyState[Button::Delete] = m_keybuffer[DIK_DELETE] & 0x80;
	m_previousKeyState[Button::Lwin] = m_keybuffer[DIK_LWIN] & 0x80;
	m_previousKeyState[Button::Rwin] = m_keybuffer[DIK_RWIN] & 0x80;
	m_previousKeyState[Button::Apps] = m_keybuffer[DIK_APPS] & 0x80;
	m_previousKeyState[Button::Sleep] = m_keybuffer[DIK_SLEEP] & 0x80;
	m_previousKeyState[Button::Left] = m_keybuffer[DIK_LEFT] & 0x80;
	m_previousKeyState[Button::Up] = m_keybuffer[DIK_UP] & 0x80;
	m_previousKeyState[Button::Right] = m_keybuffer[DIK_RIGHT] & 0x80;
	m_previousKeyState[Button::Down] = m_keybuffer[DIK_DOWN] & 0x80;
	m_previousKeyState[Button::Home] = m_keybuffer[DIK_HOME] & 0x80;
	m_previousKeyState[Button::End] = m_keybuffer[DIK_END] & 0x80;
}