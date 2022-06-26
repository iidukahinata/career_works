/**
* @file    InputEvents.h
* @brief   ���͊֌W�̃C�x���g�N���X��`
*
* @date	   2022/06/23 2022�N�x����
*/
#pragma once


#include "SubSystem/Core/Event/Event.h"

class KeyPressed : public IEvent
{
	SUB_CLASS(KeyPressed)
public:

	KeyPressed(uint32_t key);
	std::any GetData() override;

private:

	uint32_t m_key;
};

class KeyReleased : public IEvent
{
	SUB_CLASS(KeyReleased)
public:

	KeyReleased(uint32_t key);
	std::any GetData() override;

private:

	uint32_t m_key;
};