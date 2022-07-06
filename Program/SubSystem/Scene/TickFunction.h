/**
* @file    TickFunction.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


class TickFunction
{
public:

	virtual void Tick(double deltaTime) = 0;

	/** �X�V�������s�����߂ɂ́A��x���s���Ȃ���΂Ȃ�Ȃ��B*/
	void RegisterToTickManager() noexcept;

	/** TickManager �ɓo�^�����ꍇ�A�Ăяo���K�v������܂��B*/
	void UnRegisterFromTickManager() noexcept;

	/** �X�V�����̑ҋ@�A���s���Ȃ� true ��Ԃ��B*/
	bool IsRegistered() const noexcept;

	void SetEnable(bool enable) noexcept;
	bool GetEnable() noexcept;

	void SetPriority(uint32_t priority) noexcept;
	uint32_t GetPriority() const noexcept;

private:

	// * �X�V�����D��x 0 �ɋ߂��l���D�悳���B
	uint32_t m_priority = 128;

	// * �X�V�����̗L������ێ�
	bool m_isEnabled = true;

	// * TickManager �̓o�^����Ă��邩��ێ�
	bool m_isRegistered = false;
};

/**
* �R���|�[�l���g�X�V�I�u�W�F�N�g
*/
class TickComponentFunction : public TickFunction
{
public:

	class IComponent* m_component;

public:

	void Tick(double deltaTime);
};