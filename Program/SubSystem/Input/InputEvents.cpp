/**
* @file    InputEvents.cpp
* @brief   入力関係のイベントクラス定義
*
* @date	   2022/06/23 2022年度初版
*/


#include "InputEvents.h"

KeyPressed::KeyPressed(uint32_t key) : m_key(key)
{

}

const std::any& KeyPressed::GetData()
{
	return m_key;
}

KeyReleased::KeyReleased(uint32_t key) : m_key(key)
{

}


const std::any& KeyReleased::GetData()
{
	return m_key;
}