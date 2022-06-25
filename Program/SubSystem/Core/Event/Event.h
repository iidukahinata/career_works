/**
* @file		Event.h
* @brief
*
* @date		2022/06/23 2022年度初版
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

	/** リスナーオブジェクトに渡さす引数データ */
	virtual const std::any& GetData() = 0;
};