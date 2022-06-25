/**
 * @file	Context.h
 * @brief	Subsystemのサービスロケータクラス
 *
 * @date	2022/06/25 2022年度初版
 */
#pragma once


#include <map>
#include <memory>
#include "ISubsystem.h"

class Context
{
	COPY_PROHIBITED(Context)
public:

	Context() = default;

	/** 登録した Subsystem は取得時 指定 Key クラスとして取得するため継承関係になければならない。*/
	template<class Key>
	void RegisterSubsystem(std::unique_ptr<ISubsystem> subsystem) noexcept;

	/**
	* コンテナから指定サブシステムの取得
	* @retval	指定サブシステムポインタ
	* @retval	失敗時 nullptr
	*/
	template<class Key>
	Key* GetSubsystem() noexcept;

private:

	/** キーの重複が無いもとして登録。*/
	void RegisterSubsystem(uint32_t hash, ISubsystem* subsystem) noexcept;
	ISubsystem* GetSubsystemByHash(uint32_t hash) noexcept;

private:

	// * Type -> <ハッシュ、システムオブジェクト>
	std::map<uint32_t, std::unique_ptr<ISubsystem>> m_subsystems;
};

template<class Key>
FORCEINLINE void Context::RegisterSubsystem(std::unique_ptr<ISubsystem> subsystem) noexcept
{
	RegisterSubsystem(Key::TypeData.Hash, subsystem.release());
}

template<class Key>
FORCEINLINE Key* Context::GetSubsystem() noexcept
{
	return dynamic_cast<Key*>(GetSubsystemByHash(Key::TypeData.Hash));
}