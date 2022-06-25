/**
* @file    AsyncJobSystem.h
* @brief
*
* @date	   2022/06/23 2022年度初版
*/
#pragma once


#include <queue>
#include <mutex>
#include "AsyncJob.h"
#include "SubSystem/Core/Common/Macro.h"

class AsyncJobSystem
{
	AsyncJobSystem() = default;
	COPY_PROHIBITED(AsyncJobSystem)
public:

	static AsyncJobSystem& Get() noexcept
	{
		static AsyncJobSystem instance;
		return instance;
	}

	~AsyncJobSystem();

	/**
	* 指定個数 thread を使用して並列処理初期化
	* @param threadCount [入力] 並列処理で使用する thred 数を指定する。
	*/
	bool Initialize(int threadCount) noexcept;

	/**
	* 並列処理で実行される処理の追加
	* @param function [入力] 追加処理する関数を指定。
	*/
	void AddTask(AsyncJob* job) noexcept;

	/** CPU最大使用可能スレッド数を返す */
	int GetMaxThreadCount() const noexcept;

	/** インスタンスの解放時に実行される */
	void Stop() noexcept;

private:

	/** 生成された各 thread が処理する Task 実行を行う関数 */
	void ThreadLoop() noexcept;

private:

	// * 並列処理中の終了を管理する
	bool m_isRunning;

	// * タスク実行されていない thread 数を保持
	int m_numOfThreadsAvailable;

	// * 並列処理で順に実行される関数
	std::queue<AsyncJob*> m_tasks;

	// * ユーザー指定数で thread 数を変更するために可変長配列で管理
	std::vector<std::thread> m_threads;

	// * このクラス内での排他制御実現用
	std::mutex m_mutex;

	std::condition_variable m_conditionVar;
};