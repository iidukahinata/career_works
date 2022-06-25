/**
 * @file	Context.cpp
 * @brief	Subsystemのサービスロケータクラス
 *
 * @date	2022/06/23 2022年度初版
 */


#include "Context.h"

void Context::RegisterSubsystem(uint32_t hash, ISubsystem* subsystem) noexcept
{
	// 重複チェック
	ASSERT(!m_subsystems.contains(hash));

	subsystem->SetContext(this);
	m_subsystems[hash].reset(subsystem);
}

ISubsystem* Context::GetSubsystemByHash(uint32_t hash) noexcept
{
	if (m_subsystems.contains(hash))
	{
		return m_subsystems[hash].get();
	}
	return nullptr;
}