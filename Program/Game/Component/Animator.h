/**
* @file    Animator.h
* @brief
*
* @date	   2022/06/09 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include <map>
#include <functional>

/**
* 所属クラスのコードの細分化のために作成。
* Animator という名前程の機能は実現していない。
* 登録されたアニメーション関数を切り替え、疑似的なアニメーションを実現させている。
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