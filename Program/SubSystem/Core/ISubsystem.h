/**
 * @file	ISubsystem.h
 * @brief
 *
 * @date	2022/06/23 2022�N�x����
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

	/* �x���Z�b�g�A�b�v */
	void SetContext(Context* context) noexcept;
	Context* GetContext() const noexcept;

private:

	Context* m_context = nullptr;
};