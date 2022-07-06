/**
* @file		JobSystem.h
* @brief
*
* @date		2022/07/06 2022�N�x����
*/
#pragma once


#include <mutex>
#include "Job.h"

class JobSystem
{
	COPY_PROHIBITED(JobSystem)
private:

	class JobContainer
	{
	public:

		/** �萔���Ԃł̏����B*/
		void Register(Job* job) noexcept;
		void Remove(Job* job) noexcept;

		/** JobSystem���Ł@�͈� for �g�p���邽�߂ɒ�`�B*/
		auto begin() noexcept;
		auto end() noexcept;

	private:

		Set<Job*> m_jobs;
	};

public:

	JobSystem() = default;

	static JobSystem& Get()
	{
		static JobSystem jobSystem;
		return jobSystem;
	}

	/** Function Type �����ɑS�Ď��s���Ă����܂��B*/
	void Execute(double deletaTime) noexcept;

	/** �w�� Function Type �����s���Ă����܂��B*/
	void Execute(double deletaTime, FunctionType mode) noexcept;

	/** Thread Safe �Ȋ֐��ł��B*/
	bool RegisterJob(Job* job) noexcept;
	void RemoveJob(Job* job) noexcept;

private:

	std::mutex m_mutex;

	// * Type -> <�^�C�vID�A�R���e�i>
	Map<FunctionType, JobContainer> m_containers;
};