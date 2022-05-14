/**
* @file    COM.h
* @brief
*
* @date	   2022/05/14 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


enum class COMID
{
	MULTITHREADED = 0x0,		// OLE calls objects on any thread.
	APARTMENTTHREADED = 0x2,	// Apartment model
	DISABLE_OLE1DDE = 0x4,		// Don't use DDE for Ole1 support.
	SPEED_OVER_MEMORY = 0x8,	// Trade memory for speed.
};

/**
* DirectTex �� COM ������������Ă��Ȃ����߁A�ǂݍ��ݏ��������s���邽�߁B
* COM ���C�u�������������������邽�ߍ쐬�B
*/
class COM
{
public:

	COM();
	COM(COMID comID);

	~COM();
};