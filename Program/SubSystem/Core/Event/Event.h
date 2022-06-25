/**
* @file		Event.h
* @brief
*
* @date		2022/06/23 2022年度初版
*/
#pragma once


#include <any>
#include "../Common/Macro.h"

/* Event 派生クラスで必ず定義するマクロ定義 */
#define EVENT_CLASS(CLASS, NAME)						\
SUB_CLASS(CLASS)										\
static INLINE EventType Type##CLASS = EventType(#NAME); \
const EventType& GetEventType() override				\
{														\
	return Type##CLASS;									\
}

/**
* 名前から EventType を識別するために作成。
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

	/* リスナーオブジェクトとのリンクに使用 */
	virtual const EventType& GetEventType() = 0;

	/* リスナーオブジェクトに渡さす引数データ */
	virtual const std::any& GetData() = 0;
};