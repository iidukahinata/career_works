/**
* @file	   WinMain.cpp
* @brief
*
* @date	   2022/06/23 2022îNìxèâî≈
*/


#include "Subsystem/Core/Engine.h"

std::unique_ptr<Engine> engine;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	engine = std::make_unique<Engine>();

	struct AutoEngineFinish
	{
		~AutoEngineFinish() { engine->Shutdown(); }
	} autoEngineFinish;

	if (!engine->Initialize(hInstance))
	{
		return -1;
	}
	
	long ret = engine->MainLoop();

	return ret;
}