/**
* @file    Animator.cpp
* @brief
*
* @date	   2022/06/09 2022年度初版
* @author  飯塚陽太
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
	// 同じ名前のアニメーションがないようにするため
	if (m_animations.contains(name.data()))
	{
		LOG_ERROR("既に同じ名前のアニメーションが存在しています。");
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