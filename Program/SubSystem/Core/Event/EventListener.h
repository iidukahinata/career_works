/**
* @file    EventListener.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include <any>

/**
* 2022/06/22 ����AEvent �����S�̂𒊏ۉ������R�[�h�̊ȗ�����}�邽�߃��X�i�[�I�u�W�F�N�g���N���X�ɕύX�B
*/
class EventListener
{
	SUPER_CLASS(EventListener)
public:

	virtual void Action(std::any) = 0;
};