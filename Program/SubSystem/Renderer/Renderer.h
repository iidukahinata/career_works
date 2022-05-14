/**
* @file	   Renderer.h
* @brief
*
* @date	   2022/05/11 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


class Renderer
{
private:

	Renderer() = default;
	Renderer(const Renderer&) = default;
	Renderer& operator=(const Renderer&) = default;

public:

	static Renderer& Get() noexcept
	{
		static Renderer instance;
		return instance;
	}

	void Init();
	void BeginFream();
	void EndFream();
	void Exit();
};