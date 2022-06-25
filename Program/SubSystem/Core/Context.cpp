/**
 * @file	Context.cpp
 * @brief	Subsystem�̃T�[�r�X���P�[�^�N���X
 *
 * @date	2022/06/23 2022�N�x����
 */


#include "Context.h"

void Context::RegisterSubsystem(uint32_t hash, ISubsystem* subsystem) noexcept
{
	// �d���`�F�b�N
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