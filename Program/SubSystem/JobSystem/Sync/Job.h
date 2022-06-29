/**
* @file		Job.h
* @brief
*
* @date		2022/06/29 2022年度初版
*/
#pragma once


#include <functional>

enum FunctionType
{
	Update,

	LateUpdate,

	Render,

	LateRender,

	None,
};

class Job
{
	friend class JobSystem;

	typedef std::function<void(double)> Task;
public:

	Job() = default;
	Job(Task&& task, FunctionType type) noexcept;

	~Job();

	void Execute(double deletaTime) noexcept;

	/**
	* JobSystem で実行される関数 function を設定
	* @note
	*  引数には double 型を受け取る必要があります。
	*/
	void SetFunction(Task&& task, FunctionType fincType) noexcept;

private:

	// * JobSystem セット後実行させる関数
	Task m_task;

	// * 検索用に所属コンテナのポインタを保持します。
	FunctionType m_funcType = FunctionType::None;
};