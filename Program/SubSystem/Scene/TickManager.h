/**
* @file    TickManager.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


class TickFunction;

class TickManager
{
	typedef Set<TickFunction*> TickContainer;
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
	Set<TickFunction*> m_allTickFunctions;

	// * -> �D��x : �R���e�i (enable �ݒ肳��Ă��� TickFunction �̂ݕێ�)
	Map<uint32_t, TickContainer> m_tickContainers;
};