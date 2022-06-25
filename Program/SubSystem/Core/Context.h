/**
 * @file	Context.h
 * @brief	Subsystem�̃T�[�r�X���P�[�^�N���X
 *
 * @date	2022/06/25 2022�N�x����
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

	/** �o�^���� Subsystem �͎擾�� �w�� Key �N���X�Ƃ��Ď擾���邽�ߌp���֌W�ɂȂ���΂Ȃ�Ȃ��B*/
	template<class Key>
	void RegisterSubsystem(std::unique_ptr<ISubsystem> subsystem) noexcept;

	/**
	* �R���e�i����w��T�u�V�X�e���̎擾
	* @retval	�w��T�u�V�X�e���|�C���^
	* @retval	���s�� nullptr
	*/
	template<class Key>
	Key* GetSubsystem() noexcept;

private:

	/** �L�[�̏d�����������Ƃ��ēo�^�B*/
	void RegisterSubsystem(uint32_t hash, ISubsystem* subsystem) noexcept;
	ISubsystem* GetSubsystemByHash(uint32_t hash) noexcept;

private:

	// * Type -> <�n�b�V���A�V�X�e���I�u�W�F�N�g>
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