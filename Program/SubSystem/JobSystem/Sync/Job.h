/**
* @file		Job.h
* @brief
*
* @date		2022/06/23 2022年度初版
*/
#pragma once


#include <functional>

class Job
{
	typedef std::function<void(double)> Task;
	typedef void* Pointer;
public:

	Job() = default;
	Job(Task&& task) noexcept;

	~Job();

	void Execute(double deletaTime) noexcept;

	/**
	* JobSystem で実行される関数 function を設定
	* @note
	*  引数には double 型を受け取る必要があります。
	*/
	void SetFunction(Task&& task) noexcept;

	/* 所属コンテナで使用される関数です。 */
	void SetPointer(Pointer jobContainer) noexcept;
	Pointer GetPointer() const noexcept;
	void SetId(uint32_t id) noexcept;
	uint32_t GetId() const noexcept;

private:

	//* JobSystem セット後実行させる関数
	Task m_task;

	//* 検索用に所属コンテナのポインタを保持します。
	Pointer m_jobContainer = nullptr;

	//* コンテナでの配列の要素位置を保持します。
	uint32_t m_id = -1;
};