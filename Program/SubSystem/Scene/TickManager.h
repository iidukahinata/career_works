/**
* @file    TickManager.h
* @brief
*
* @date	   2022/06/30 2022�N�x����
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

	/** �X�V�������s�����߂ɁA�Ăяo���K�v������܂��B*/
	void RegisterTickFunction(TickFunction* function) noexcept;
	void UnRegisterTickFunction(TickFunction* function) noexcept;

	/** TickFunction �̐ݒ肪�ύX���ꂽ���ɌĂяo���B*/
	void AddTickFunction(TickFunction* function) noexcept;

	/** TickFunction �̐ݒ肪�ύX��O�Ɏ��ɌĂяo���K�v������܂��B*/
	void RemoveTickFunction(TickFunction* function) noexcept;

	/** �X�V�����̂��߂ɓo�^����Ă��邩�𔻕ʁB*/
	bool HasTickFunction(TickFunction* function) noexcept;

private:

	// * enable �ݒ��킸�X�V�������s���\�������� TickFunction ��ێ��B
	std::set<TickFunction*> m_allTickFunctions;

	// * -> �D��x : �R���e�i (enable �ݒ肳��Ă��� TickFunction �̂ݕێ�)
	std::map<uint32_t, TickContainer> m_tickContainers;
};