/**
* @file    Application.h
* @brief
*
* @date	   2022/04/29 2022îNìxèâî≈
* @author  î—íÀózëæ
*/
#pragma once


#include <Windows.h>

class Application
{
private:

	Application() = default;
	Application(const Application&) = default;
	Application& operator=(const Application&) = default;

public:

	static Application& Get() noexcept
	{
		static Application instance;
		return instance;
	}

	bool Init(HINSTANCE hInstance);
	long MainLoop();
	void Exit();

private:

	HINSTANCE m_hInstance;
};