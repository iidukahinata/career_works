/**
* @file    EventManager.cpp
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/


#include "EventManager.h"
#include "EventListener.h"

void EventManager::Initialize()
{
	// ���C���X���b�h�W���u�Ƃ��ăC�x���g���[�v��o�^���Ă��邪�A���X���b�h�ŏ������������S���Ă�������������Ȃ��B
	m_job.SetFunction([this](double) { Tick(); }, FunctionType::Update);
	m_job.RegisterToJobSystem();
}

void EventManager::Exit()
{
	m_job.UnRegisterFromJobSystem();

	m_eventListeners.clear();
	
	for (size_t i = 0; i < m_eventQueues.max_size(); ++i)
	{
		m_eventQueues[i].clear();
	}

	m_numActiveQueue = 0;
}

bool EventManager::AddToQueue(UniquePtr<IEvent> eventBase) noexcept
{
	auto& eventType = eventBase->GetTypeData();

	// ������ Event ��o�^���Ȃ�����
	if (eventType.Name.size() == 0)
	{
		return false;
	}

	// �w��p�̃��X�i�[�R���e�i���Ȃ���Ώ���������̂��Ȃ��̂Œǉ����Ȃ��B
	if (m_eventListeners.contains(eventType.Hash))
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_eventQueues[m_numActiveQueue].push_back(eventBase.Release());
		return true;
	}
	return false;
}

void EventManager::RemoveFromQueue(EventType eventType, bool isAll) noexcept
{
	// ������ Event �͓o�^����Ă��Ȃ�����
	if (eventType.Name.size() == 0)
	{
		return;
	}

	// ���X�i�[�R���e�i����������Ă��Ȃ����͌��X�L���[�ɒǉ�����Ă��Ȃ�����
	if (!m_eventListeners.contains(eventType.Hash))
	{
		return;
	}

	std::unique_lock<std::mutex> lock(m_mutex);

	auto& eventQueue = m_eventQueues[m_numActiveQueue];
	for (auto it = eventQueue.begin(); it != eventQueue.end();)
	{
		if ((*it)->GetTypeData() == eventType)
		{
			it = eventQueue.erase(it);
			if (!isAll) break;
		}
		else
		{
			it++;
		}
	}
}

bool EventManager::AddEventLisener(EventListener* eventListener, const EventType& eventType) noexcept
{
	// ������ Event ��o�^���Ȃ�����
	if (eventType.Name.size() == 0)
	{
		return false;
	}

	// ���X�i�[�̏d��������邽��
	if (m_eventListeners[eventType.Hash].contains(eventListener))
	{
		return false;
	}

	std::unique_lock<std::mutex> lock(m_mutex);
	m_eventListeners[eventType.Hash].insert(eventListener);

	return true;
}

bool EventManager::RemoveEventLisener(EventListener* eventListener, const EventType& eventType) noexcept
{
	// ������ Event ���������Ȃ�����
	if (eventType.Name.size() == 0)
	{
		return true;
	}

	std::unique_lock<std::mutex> lock(m_mutex);
	auto numErase = m_eventListeners[eventType.Hash].erase(eventListener);

	// �������ꂽ���𒲂ׂ邽��
	return numErase > 0;
}

void EventManager::Tick() noexcept
{
	// �L���[�̓���ւ�
	auto numQueue = m_numActiveQueue;
	(++m_numActiveQueue) %= m_eventQueues.max_size();
	m_eventQueues[m_numActiveQueue].clear();

	while (m_eventQueues[numQueue].size() != 0)
	{
		auto& event = m_eventQueues[numQueue].front();
		m_eventQueues[numQueue].pop_front();

		auto listeners = m_eventListeners[event->GetTypeData().Hash];
		for (auto listener : listeners)
		{
			listener->Action(event->GetData());
		}

		// �^�C���A�E�g�������L�q�\��B
	}

	// �^�C���A�E�g�������N�����ꍇ�A�c�����^�X�N�����t���[���Ɏ����z���B
	//m_eventQueues[m_numActiveQueue] = m_eventQueues[numQueue];
}