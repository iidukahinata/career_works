/**
* @file    EventManager.h
* @brief
*
* @date	   2022/07/06 2022年度初版
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

	/** Engine Shutdown 時に、呼び出される必要があります。*/
	void Exit();

	/** イベントを次フレーム処理用キューに追加 */
	bool AddToQueue(UniquePtr<IEvent> eventBase) noexcept;

	/**
	* 先頭にある指定イベントタイプの消去
	* isAll 指定で先頭を含めた全ての指定イベントタイプを消去
	*/
	void RemoveFromQueue(EventType eventType, bool isAll) noexcept;

	/** @param eventType [入力] 通知対応させるイベントタイプを指定。*/
	bool AddEventLisener(EventListener* eventListener, const EventType& eventType) noexcept;
	bool RemoveEventLisener(EventListener* eventListener, const EventType& eventType) noexcept;

private:

	/** 前フレームで発生したイベントを処理します。*/
	void Tick() noexcept;

private:

	// * キューが一つの場合イベントがイベント呼び出し処理が終わらない可能性があるため複数用意する
	Array<List<UniquePtr<IEvent>>, 2> m_eventQueues;

	// * -> ハッシュ値 : リスナーポインタ配列
	Map<uint32_t, Set<EventListener*>> m_eventListeners;

	// * 現在使用中キュー番号
	int m_numActiveQueue = 0;

	std::mutex m_mutex;

	/* Event Update の登録用 */
	Job m_job;
};