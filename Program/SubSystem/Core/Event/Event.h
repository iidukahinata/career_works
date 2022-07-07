/**
* @file		Event.h
* @brief
*
* @date		2022/07/06 2022�N�x����
*/
#pragma once


typedef ClassTypeData EventType;

class IEvent
{
	SUPER_CLASS(IEvent)
	COPY_PROHIBITED(IEvent)
public:

	IEvent() = default;
	virtual ~IEvent() = default;

	/** ���X�i�[�I�u�W�F�N�g�ɓn���������f�[�^ */
	virtual std::any GetData() = 0;
};