/**
* @file    TickFunction.h
* @brief
*
* @date	   2022/06/30 2022�N�x����
*/
#pragma once


#include <stdint.h>

class TickFunction
{
public:

	virtual void Tick(double deltaTime) = 0;

	void RegisterToTickManager() noexcept;
	void UnRegisterFromTickManager() noexcept;

	bool IsRegistered() noexcept;

	void SetPriority(uint32_t priority) noexcept;
	uint32_t GetPriority() const { return m_priority; }

private:

	// * �X�V�����D��x 0 �ɋ߂��l���D�悳���B
	uint32_t m_priority = 128;
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