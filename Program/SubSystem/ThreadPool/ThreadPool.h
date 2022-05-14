/**
* @file    ThreadPool.h
* @brief	並列処理クラス
*
* @date	   2022/05/14 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include <queue>
#include <mutex>
#include <functional>

class ThreadPool
{
private:

	ThreadPool() = default;
	ThreadPool(const ThreadPool&) = default;
	ThreadPool& operator=(const ThreadPool&) = default;

public:

	static ThreadPool& Get() noexcept
	{
		static ThreadPool instance;
		return instance;
	}

	~ThreadPool();

	/**
	* 指定個数 thread を使用して並列処理初期化
	* @param threadCount [入力] 並列処理で使用する thred 数を指定する。
	*							0 以下の場合は処理されない。
	*							CPU内のスレッド数より大きい場合も処理されない。
	*/
	bool Init(int threadCount) noexcept;

	typedef std::function<void()> ThreadClosure;

	/**
	* 並列処理で実行される処理の追加
	* @param function [入力] 追加処理する関数を指定。
	*						 null指定を想定していない。
	*/
	void AddTask(ThreadClosure&& function) noexcept;

	/**
	* 登録されたタスクが全て終了するまで待機 
	* 
	* @note
	*  2022/04/24時点ではsleepforを使用した待ちを実装していない。
	*/
	bool WaitForAllTasksToFinish() const noexcept;

	/** CPU最大使用可能スレッド数を返す */
	int GetMaxThreadCount() const noexcept;

private:

	/** インスタンスの解放時に実行される */
	void Stop() noexcept;

	/** 生成された各 thread が処理する Task 実行を行う関数 */
	void ThreadLoop() noexcept;

private:

	// * 並列処理中の終了を管理する
	bool m_isRunning;

	// * タスク実行されていない thread 数を保持
	int m_numOfThreadsAvailable;

	// * 並列処理で順に実行される関数
	std::queue<ThreadClosure> m_tasks;

	// * ユーザー指定数で thread 数を変更するために可変長配列で管理
	std::vector<std::thread> m_threads;

	// * このクラス内での排他制御実現用
	std::mutex m_mutex;

	std::condition_variable m_conditionVar;
};