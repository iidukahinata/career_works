/**
* @file    COM.h
* @brief
*
* @date	   2022/05/14 2022年度初版
* @author  飯塚陽太
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
* DirectTex で COM が初期化されていないため、読み込み処理が失敗するため。
* COM ライブラリを初期化生成するため作成。
*/
class COM
{
public:

	COM();
	COM(COMID comID);

	~COM();
};