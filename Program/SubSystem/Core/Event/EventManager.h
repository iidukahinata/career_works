/**
* @file    EventManager.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include <mutex>
#include "Event.h"
#include "SubSystem/JobSystem/Sync/Job.h"

class EventListener;

class EventManager
{
	EventManager() = default;
	COPY_PROHIBITED(EventManager)
public:

	static EventManager& Get() noexcept
	{
		static EventManager instance;
		return instance;
	}

	void Initialize();

	/** Engine Shutdown ���ɁA�Ăяo�����K�v������܂��B*/
	void Exit();

	/** �C�x���g�����t���[�������p�L���[�ɒǉ� */
	bool AddToQueue(UniquePtr<IEvent> eventBase) noexcept;

	/**
	* �擪�ɂ���w��C�x���g�^�C�v�̏���
	* isAll �w��Ő擪���܂߂��S�Ă̎w��C�x���g�^�C�v������
	*/
	void RemoveFromQueue(EventType eventType, bool isAll) noexcept;

	/** @param eventType [����] �ʒm�Ή�������C�x���g�^�C�v���w��B*/
	bool AddEventLisener(EventListener* eventListener, const EventType& eventType) noexcept;
	bool RemoveEventLisener(EventListener* eventListener, const EventType& eventType) noexcept;

private:

	/** �O�t���[���Ŕ��������C�x���g���������܂��B*/
	void Tick() noexcept;

private:

	// * �L���[����̏ꍇ�C�x���g���C�x���g�Ăяo���������I���Ȃ��\�������邽�ߕ����p�ӂ���
	Array<List<UniquePtr<IEvent>>, 2> m_eventQueues;

	// * -> �n�b�V���l : ���X�i�[�|�C���^�z��
	Map<uint32_t, Set<EventListener*>> m_eventListeners;

	// * ���ݎg�p���L���[�ԍ�
	int m_numActiveQueue = 0;

	std::mutex m_mutex;

	/* Event Update �̓o�^�p */
	Job m_job;
};