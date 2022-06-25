/**
 * @file	ISubsystem.cpp
 * @brief
 *
 * @date	2022/06/23 2022îNìxèâî≈
 */


#include "ISubsystem.h"
#include "Context.h"

void ISubsystem::SetContext(Context* context) noexcept
{
    if (!m_context) m_context = context;
}

Context* ISubsystem::GetContext() const noexcept
{
    return m_context;
}