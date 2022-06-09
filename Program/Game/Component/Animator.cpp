/**
* @file    Animator.cpp
* @brief
*
* @date	   2022/06/09 2022�N�x����
* @author  �ђ˗z��
*/


#include "Animator.h"
#include "SubSystem/Log/DebugLog.h"

void Animator::Update()
{
	if (IsPlaying())
	{
		m_animations[m_currentAnimName]();
	}
}

bool Animator::RegisterAnimation(std::string_view name, Animation&& animation) noexcept
{
	// �������O�̃A�j���[�V�������Ȃ��悤�ɂ��邽��
	if (m_animations.contains(name.data()))
	{
		LOG_ERROR("���ɓ������O�̃A�j���[�V���������݂��Ă��܂��B");
		return false;
	}

	m_animations.emplace(name.data(), animation);
	return true;
}

bool Animator::SetAnimation(std::string_view name) noexcept
{
	if (m_animations.contains(name.data()))
	{
		m_currentAnimName = name.data();
		return true;
	}

	m_currentAnimName = nullptr;
	return false;
}

void Animator::StopAnimation() noexcept
{
	m_currentAnimName = nullptr;
}

bool Animator::IsPlaying() const noexcept
{
	return !(m_currentAnimName == nullptr);
}

const char* Animator::GetCurrentAnimName() const noexcept
{
	return m_currentAnimName;
}