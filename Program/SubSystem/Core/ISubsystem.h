/**
 * @file	ISubsystem.h
 * @brief
 *
 * @date	2022/06/26 2022îNìxèâî≈
 */
#pragma once


#include "Common/Macro.h"

class Context;

class ISubsystem
{
	SUPER_CLASS(ISubsystem)
	COPY_PROHIBITED(ISubsystem)
public:

	ISubsystem() = default;
	virtual ~ISubsystem() { Shutdown(); }

	virtual bool Initialize() { return true; }
	virtual void Shutdown() {}

	Context* GetContext() const noexcept;
};