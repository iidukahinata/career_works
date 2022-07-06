/**
* @file    Engine.h
* @brief
*
* @date	   2022/06/26 2022�N�x����
*/
#pragma once


#include <Windows.h>

class Engine
{
	COPY_PROHIBITED(Engine)
public:

	Engine() = default;

	/** �A�v���P�[�V�����S�̂̃Z�b�g�A�b�v���s���܂��B*/
	bool Initialize(HINSTANCE hInstance);

	/** �G���W�����[�v���������܂��B*/
	long MainLoop();

	/**
	* ���̊֐��� JobSystem ����������O�ɌĂяo���K�v������܂��B
	* �e�V�X�e�����Z�b�g���� Job ��������̂��� JobSystem �ɃA�N�Z�X���邽�߂ł��B
	*/
	void Shutdown();

private:

	/** ��ɁA�ʏ�̃E�B���h�E�ƃf�o�b�N�E�B���h�E�𐶐����܂��B*/
	bool StartUpScreen(HINSTANCE hInstance) noexcept;

	/** �e�V�X�e���N���X�̐������s���B*/
	void RegisterSubsystemsToContainer() noexcept;

	/** �o�^���ꂽ�e�V�X�e���̃Z�b�g�A�b�v���s���B*/
	bool InitializeSubsystems() noexcept;

private:

	HINSTANCE m_hInstance;
};