/**
* @file    Engine.h
* @brief
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


#include <Windows.h>
#include "Context.h"

class Engine
{
	COPY_PROHIBITED(Engine)
public:

	Engine() = default;

	/** アプリケーション全体のセットアップを行います。*/
	bool Initialize(HINSTANCE hInstance);

	/** エンジンループを実現します。*/
	long MainLoop();

	/**
	* この関数は JobSystem が解放される前に呼び出す必要があります。
	* 各システムがセットした Job 解放処理のため JobSystem にアクセスするためです。
	*/
	void Shutdown();

private:

	/** 主に、通常のウィンドウとデバックウィンドウを生成します。*/
	bool StartUpScreen(HINSTANCE hInstance) noexcept;

	/** 各システムクラスの生成を行う。*/
	void RegisterSubsystemsToContainer() noexcept;

	/** 登録された各システムのセットアップを行う。*/
	bool InitializeSubsystems() noexcept;

private:

	HINSTANCE m_hInstance;

	UniquePtr<Context> m_context;
};