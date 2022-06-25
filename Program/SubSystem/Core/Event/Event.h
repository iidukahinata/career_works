/**
* @file		Event.h
* @brief
*
* @date		2022/06/23 2022�N�x����
*/
#pragma once


#include <any>
#include "../Common/Macro.h"

/* Event �h���N���X�ŕK����`����}�N����` */
#define EVENT_CLASS(CLASS, NAME)						\
SUB_CLASS(CLASS)										\
static INLINE EventType Type##CLASS = EventType(#NAME); \
const EventType& GetEventType() override				\
{														\
	return Type##CLASS;									\
}

/**
* ���O���� EventType �����ʂ��邽�߂ɍ쐬�B
*/
struct EventType
{
	const uint32_t Hash;
	const std::string_view Str;

	constexpr EventType(std::string_view name) : Hash(GetHashFromCRC(name)), Str(name)
	{}

	bool operator==(const EventType& eventType)
	{
		return Hash == eventType.Hash;
	}
};

class IEvent
{
	SUPER_CLASS(IEvent)
	COPY_PROHIBITED(IEvent)
public:

	IEvent() = default;
	virtual ~IEvent() = default;

	/* ���X�i�[�I�u�W�F�N�g�Ƃ̃����N�Ɏg�p */
	virtual const EventType& GetEventType() = 0;

	/* ���X�i�[�I�u�W�F�N�g�ɓn���������f�[�^ */
	virtual const std::any& GetData() = 0;
};