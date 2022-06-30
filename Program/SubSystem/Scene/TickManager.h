/**
* @file    TickManager.h
* @brief
*
* @date	   2022/06/30 2022年度初版
*/
#pragma once


#include <map>
#include <set>
#include "TickFunction.h"

class TickManager
{
	typedef std::set<TickFunction*> TickContainer;
public:

	static TickManager& Get()
	{
		static TickManager instance;
		return instance;
	}

	void Tick(double deltaTime) noexcept;

	/** 更新処理を行うために、呼び出す必要があります。*/
	void RegisterTickFunction(TickFunction* function) noexcept;
	void UnRegisterTickFunction(TickFunction* function) noexcept;

	/** TickFunction の設定が変更された時に呼び出す。*/
	void AddTickFunction(TickFunction* function) noexcept;

	/** TickFunction の設定が変更る前に時に呼び出す必要があります。*/
	void RemoveTickFunction(TickFunction* function) noexcept;

	/** 更新処理のために登録されているかを判別。*/
	bool HasTickFunction(TickFunction* function) noexcept;

private:

	// * enable 設定問わず更新処理を行う可能性がある TickFunction を保持。
	std::set<TickFunction*> m_allTickFunctions;

	// * -> 優先度 : コンテナ (enable 設定されている TickFunction のみ保持)
	std::map<uint32_t, TickContainer> m_tickContainers;
};