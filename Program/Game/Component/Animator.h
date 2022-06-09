/**
* @file    Animator.h
* @brief
*
* @date	   2022/06/09 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include <map>
#include <functional>

/**
* �����N���X�̃R�[�h�̍ו����̂��߂ɍ쐬�B
* Animator �Ƃ������O���̋@�\�͎������Ă��Ȃ��B
* �o�^���ꂽ�A�j���[�V�����֐���؂�ւ��A�^���I�ȃA�j���[�V���������������Ă���B
*/
class Animator
{
public:

	typedef std::function<void()> Animation;

	void Update();

	bool RegisterAnimation(std::string_view name, Animation&& animation) noexcept;
	bool SetAnimation(std::string_view name) noexcept;
	void StopAnimation() noexcept;

	const char* GetCurrentAnimName() const noexcept;

	bool IsPlaying() const noexcept;

private:

	// -> name : animation func
	std::map<const char*, Animation> m_animations;

	const char* m_currentAnimName = nullptr;
};