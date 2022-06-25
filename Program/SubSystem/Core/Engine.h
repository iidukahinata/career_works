/**
* @file    Engine.h
* @brief
*
* @date	   2022/06/23 2022年度初版
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
	* この関数は JobSystem が解放される前に呼び出す必要があります。
	* 理由は各システムがセットした Job が自身の解放処理のため JobSystem にアクセスするためです。
	*/
	void Shutdown();

private:

	bool StartUpScreen(HINSTANCE hInstance) noexcept;
	void RegisterSubsystemsToContainer() noexcept;
	bool InitializeSubsystems() noexcept;

private:

	HINSTANCE m_hInstance;

	/* Subsystem 管理のコンテナクラス */
	std::unique_ptr<Context> m_context;
};