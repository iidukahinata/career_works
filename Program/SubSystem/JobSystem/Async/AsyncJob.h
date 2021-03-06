/**
* @file		AsyncJob.h
* @brief
*
* @date		2022/07/08 2022年度初版
*/
#pragma once


class AsyncJob
{
	typedef std::function<void()> Task;
public:

	AsyncJob() = default;
	AsyncJob(Task&& task) noexcept;

	AsyncJob(const AsyncJob&);
	AsyncJob& operator=(const AsyncJob&);

	void Execute() noexcept;

	/** JobSystem で実行される関数 function を設定。*/
	void SetFunction(Task&& task) noexcept;

	/** JobSystem で実行されるメンバ関数 function を設定。*/
	template<class T, class Func>
	void SetFunction(T* ptr, Func task) noexcept;

	bool IsTaskFinish() const noexcept;

	/** 実行する処理をタスクに追加。*/
	void RegisterToJobSystem();

private:

	// * 非同期実行させるタスク処理。
	Task m_task;

	// * タスク処理が完了したかを保持する。
	std::atomic_bool m_finish;
};

template<class T, class Func>
inline void AsyncJob::SetFunction(T* ptr, Func task) noexcept
{
	m_task = std::bind(&task, ptr);
}