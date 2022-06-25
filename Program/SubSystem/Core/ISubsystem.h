/**
 * @file	ISubsystem.h
 * @brief
 *
 * @date	2022/06/23 2022�N�x����
 */
#pragma once


#include "Common/Macro.h"

class Context;

class ISubsystem
{
	SUPER_CLASS(ISubsystem)
	COPY_PROHIBITED(ISubsystem)
public:

	ISubsystem() = default;
	virtual ~ISubsystem() { Shutdown(); }

	virtual bool Initialize() { return true; }
	virtual void Shutdown() {}

	/* �w��I�u�W�F�N�g�� this �Ɠ����^�̎� true ��Ԃ��܂��B*/
	template<class T>
	bool IsSameClass(T* obj) const noexcept;
	
	/* �e���v���[�g�^�� this �Ɠ����^�̎� true ��Ԃ��܂��B*/
	template<class T>
	bool IsSameClass() const noexcept;

	/* �x���Z�b�g�A�b�v */
	void SetContext(Context* context) noexcept;
	Context* GetContext() const noexcept;

private:

	Context* m_context = nullptr;
};

template<class T>
FORCEINLINE bool ISubsystem::IsSameClass(T* obj) const noexcept
{
	if (obj)
	{
		return TypeInfo() == obj->TypeInfo();
	}
	return false;
}

template<class T>
FORCEINLINE bool ISubsystem::IsSameClass() const noexcept
{
	return TypeInfo() == typeid(T);
}