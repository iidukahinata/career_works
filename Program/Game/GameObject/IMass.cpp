/**
* @file    IMass.cpp
* @brief
*
* @date	   2022/06/02 2022�N�x����
* @author  �ђ˗z��
*/


#include "IMass.h"

const char* IMass::GetName()
{
    return nullptr;
}

void IMass::SetMassPos(Math::Vector3i pos) noexcept
{
    m_massPos = pos;
}