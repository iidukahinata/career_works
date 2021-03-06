/**
 * @file	Context.cpp
 * @brief	Subsystemのサービスロケータクラス
 *
 * @date	2022/06/26 2022年度初版
 */


#include "Context.h"

void Context::Release()
{
	m_subsystems.clear();
}

void Context::RegisterSubsystem(uint32_t hash, ISubsystem* subsystem) noexcept
{
	// 重複チェック
	ASSERT(!m_subsystems.contains(hash));

	m_subsystems[hash].Reset(subsystem);
}

ISubsystem* Context::GetSubsystemByHash(uint32_t hash) noexcept
{
	if (m_subsystems.contains(hash))
	{
		return m_subsystems[hash].Get();
	}
	return nullptr;
}