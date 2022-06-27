/**
* @file	   WinMain.cpp
* @brief
*
* @date	   2022/06/26 2022îNìxèâî≈
*/


#include <memory>
#include "Subsystem/Core/Engine.h"

std::unique_ptr<Engine> g_engine;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	g_engine = std::make_unique<Engine>();

	struct AutoEngineFinish
	{
		~AutoEngineFinish() { g_engine->Shutdown(); }
	} autoEngineFinish;

	if (!g_engine->Initialize(hInstance))
	{
		return -1;
	}
	
	long ret = g_engine->MainLoop();

	return ret;
}