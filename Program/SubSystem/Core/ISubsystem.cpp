/**
 * @file	ISubsystem.cpp
 * @brief
 *
 * @date	2022/06/26 2022”N“x‰”Å
 */


#include "ISubsystem.h"
#include "Context.h"

Context* ISubsystem::GetContext() const noexcept
{
	return &Context::Get();
}