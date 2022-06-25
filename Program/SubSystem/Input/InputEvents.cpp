/**
* @file    InputEvents.cpp
* @brief   ���͊֌W�̃C�x���g�N���X��`
*
* @date	   2022/06/23 2022�N�x����
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