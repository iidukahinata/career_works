/**
* @file    EventListener.h
* @brief
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


#include <any>

/**
* 2022/06/22 から、Event 処理全体を抽象化させコードの簡略化を図るためリスナーオブジェクトをクラスに変更。
*/
class EventListener
{
	SUPER_CLASS(EventListener)
public:

	virtual void Action(std::any) = 0;
};