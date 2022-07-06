/**
* @file    PostProcessEffect.h
* @brief
*
* @date	   2022/07/06 2022îNìxèâî≈
*/
#pragma once


#include "../IComponent.h"

class Renderer;

class PostProcessEffect : public IComponent
{
public:

	void Initialize() override;
	void Remove() override;

	void Active(bool isActive) override;

private:

	void RegisterToRenderer();
	void OnRegisterFromRenderer();

private:

	Renderer* m_renderer;
};