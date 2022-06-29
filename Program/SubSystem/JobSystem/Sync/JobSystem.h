/**
* @file		JobSystem.h
* @brief
*
* @date		2022/06/29 2022年度初版
*/
#pragma once


#include <set>
#include <map>
#include <mutex>
#include "Job.h"
#include "SubSystem/Core/Common/Macro.h"

class JobSystem
{
	COPY_PROHIBITED(JobSystem)
private:

	class JobContainer
	{
	public:

		/** 定数時間での処理。*/
		void Register(Job* job) noexcept;
		void Remove(Job* job) noexcept;

		/** JobSystem内で　範囲 for 使用するために定義。*/
		auto begin() noexcept;
		auto end() noexcept;

	private:

		std::set<Job*> m_jobs;
	};

public:

	JobSystem() = default;

	static JobSystem& Get()
	{
		static JobSystem jobSystem;
		return jobSystem;
	}

	/** Function Type を順に全て実行していきます。*/
	void Execute(double deletaTime) noexcept;

	/** 指定 Function Type を実行していきます。*/
	void Execute(double deletaTime, FunctionType mode) noexcept;

	/** Thread Safe な関数です。*/
	bool RegisterJob(Job* job) noexcept;
	void RemoveJob(Job* job) noexcept;

private:

	std::mutex m_mutex;

	// * Type -> <タイプID、コンテナ>
	std::map<FunctionType, JobContainer> m_containers;
};