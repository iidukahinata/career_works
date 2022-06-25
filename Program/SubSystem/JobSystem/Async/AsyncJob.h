/**
* @file		AsyncJob.h
* @brief
*
* @date		2022/06/16 2022�N�x����
*/
#pragma once


#include <functional>

class AsyncJob
{
	typedef std::function<void()> Task;
public:

	void Execute() noexcept;

	/**
	* JobSystem �Ŏ��s�����֐� function ��ݒ�
	*/
	void SetFunction(Task&& task) noexcept;

	/**
	* JobSystem �Ŏ��s����郁���o�֐� function ��ݒ�
	*/
	template<class T, class Func>
	void SetFunction(T* ptr, Func task) noexcept;

	bool IsTaskFinish() const noexcept;

private:

	//* �񓯊����s������^�X�N�����B
	Task m_task;

	//* �^�X�N������������������ێ�����B
	std::atomic_bool m_finish = false;
};

template<class T, class Func>
inline void AsyncJob::SetFunction(T* ptr, Func task) noexcept
{
	m_task = std::bind(&task, ptr);
}