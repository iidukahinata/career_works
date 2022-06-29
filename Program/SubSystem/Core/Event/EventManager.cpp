/**
* @file    EventManager.cpp
* @brief
*
* @date	   2022/06/23 2022年度初版
*/


#include "EventManager.h"
#include "SubSystem/JobSystem/Sync/JobSystem.h"

void EventManager::Initialize()
{
	// メインスレッドジョブとしてイベントループを登録しているが、他スレッドで処理し処理分担してもいいかもしれない。
	m_job.SetFunction([this](double) { Tick(); }, FunctionType::Update);
	JobSystem::Get().RegisterJob(&m_job);
}

void EventManager::Exit()
{
	JobSystem::Get().RemoveJob(&m_job);

	m_eventListeners.clear();
	m_eventQueues->clear();
	m_numActiveQueue = 0;
}

bool EventManager::AddToQueue(std::shared_ptr<IEvent> eventBase) noexcept
{
	auto& eventType = eventBase->GetTypeData();

	// 無効な Event を登録しないため
	if (eventType.Name.size() == 0)
	{
		return false;
	}

	// 指定用のリスナーコンテナがなければ処理するものがないので追加しない。
	if (m_eventListeners.contains(eventType.Hash))
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_eventQueues[m_numActiveQueue].push_back(eventBase);
		return true;
	}
	return false;
}

void EventManager::RemoveFromQueue(EventType eventType, bool isAll) noexcept
{
	// 無効な Event は登録されていないため
	if (eventType.Name.size() == 0)
	{
		return;
	}

	// リスナーコンテナが生成されていない時は元々キューに追加されていないため
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
	// 無効な Event を登録しないため
	if (eventType.Name.size() == 0)
	{
		return false;
	}

	// リスナーの重複を避けるため
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
	// 無効な Event を検索しないため
	if (eventType.Name.size() == 0)
	{
		return true;
	}

	std::unique_lock<std::mutex> lock(m_mutex);
	auto numErase = m_eventListeners[eventType.Hash].erase(eventListener);

	// 消去されたかを調べるため
	return numErase > 0;
}

void EventManager::Tick() noexcept
{
	// キューの入れ替え
	auto numQueue = m_numActiveQueue;
	(++m_numActiveQueue) %= MAX_EVENT_QUEUE;
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

		// タイムアウト処理を記述予定。
	}

	// タイムアウト処理が起きた場合、残ったタスクを次フレームに持ち越す。
	//m_eventQueues[m_numActiveQueue] = m_eventQueues[numQueue];
}