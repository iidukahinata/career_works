/**
* @file    Engine.h
* @brief
*
* @date	   2022/06/23 2022�N�x����
*/
#pragma once


#include <Windows.h>
#include "Context.h"

class Engine
{
	COPY_PROHIBITED(Engine)
public:

	Engine();

	bool Initialize(HINSTANCE hInstance);
	long MainLoop();

	/**
	* ���̊֐��� JobSystem ����������O�ɌĂяo���K�v������܂��B
	* ���R�͊e�V�X�e�����Z�b�g���� Job �����g�̉�������̂��� JobSystem �ɃA�N�Z�X���邽�߂ł��B
	*/
	void Shutdown();

private:

	bool StartUpScreen(HINSTANCE hInstance) noexcept;
	void RegisterSubsystemsToContainer() noexcept;
	bool InitializeSubsystems() noexcept;

private:

	HINSTANCE m_hInstance;

	/* Subsystem �Ǘ��̃R���e�i�N���X */
	std::unique_ptr<Context> m_context;
};