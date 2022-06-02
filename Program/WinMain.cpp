/**
* @file	   WinMain.cpp
* @brief   アプリケーションクラスの操作
*
* @date	   2022/05/06 2022年度初版
* @author  飯塚陽太
*/


#include "Application/Application.h"
#include "SubSystem/Window/Window.h"

// libファイルをまとめて管理する。
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "DirectXTex.lib")
#pragma comment(lib, "assimp-vc141-mtd.lib")
#pragma comment(lib, "fmodL_vc.lib")
#pragma comment(lib, "BulletCollision.lib")
#pragma comment(lib, "BulletDynamics.lib")
#pragma comment(lib, "BulletSoftBody.lib")
#pragma comment(lib, "LinearMath.lib")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application& app = Application::Get();
	app.Init(hInstance);

	ShowWindow(Window::Get().GetHandle(), SW_SHOW);
	UpdateWindow(Window::Get().GetHandle());
	
	long ret = app.MainLoop();

	app.Exit();

	return ret;
}