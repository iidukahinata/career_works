/**
* @file		AsyncJob.h
* @brief
*
* @date		2022/06/30 2022�N�x����
*/
#pragma once


#include <functional>

class AsyncJob
{
	typedef std::function<void()> Task;
public:

	void Execute() noexcept;

	/** JobSystem �Ŏ��s�����֐� function ��ݒ�B*/
	void SetFunction(Task&& task) noexcept;

	/** JobSystem �Ŏ��s����郁���o�֐� function ��ݒ�B*/
	template<class T, class Func>
	void SetFunction(T* ptr, Func task) noexcept;

	bool IsTaskFinish() const noexcept;

	/** ���s���鏈�����^�X�N�ɒǉ��B*/
	void AddToJobSystem();

private:

	// * �񓯊����s������^�X�N�����B
	Task m_task;

	// * �^�X�N������������������ێ�����B
	std::atomic_bool m_finish = false;
};

template<class T, class Func>
inline void AsyncJob::SetFunction(T* ptr, Func task) noexcept
{
	m_task = std::bind(&task, ptr);
}