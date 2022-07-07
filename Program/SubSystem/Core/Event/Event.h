/**
* @file		Event.h
* @brief
*
* @date		2022/07/06 2022年度初版
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

	/** リスナーオブジェクトに渡さす引数データ */
	virtual std::any GetData() = 0;
};