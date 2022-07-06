/**
* @file	   WinMain.cpp
* @brief
*
* @date	   2022/07/06 2022îNìxèâî≈
*/


#include "Subsystem/Core/Engine.h"

UniquePtr<Engine> g_engine;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	g_engine = MakeUnique<Engine>();

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