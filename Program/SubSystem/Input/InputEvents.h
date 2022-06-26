/**
* @file    InputEvents.h
* @brief   入力関係のイベントクラス定義
*
* @date	   2022/06/23 2022年度初版
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