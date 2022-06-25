/**
* @file		Event.h
* @brief
*
* @date		2022/06/23 2022�N�x����
*/
#pragma once


#include <any>
#include "../Common/Macro.h"

typedef ClassTypeData EventType;

class IEvent
{
	SUPER_CLASS(IEvent)
	COPY_PROHIBITED(IEvent)
public:

	IEvent() = default;
	virtual ~IEvent() = default;

	/** ���X�i�[�I�u�W�F�N�g�ɓn���������f�[�^ */
	virtual const std::any& GetData() = 0;
};