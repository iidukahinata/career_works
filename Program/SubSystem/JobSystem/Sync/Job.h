/**
* @file		Job.h
* @brief
*
* @date		2022/06/29 2022�N�x����
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
	* JobSystem �Ŏ��s�����֐� function ��ݒ�
	* @note
	*  �����ɂ� double �^���󂯎��K�v������܂��B
	*/
	void SetFunction(Task&& task, FunctionType fincType) noexcept;

private:

	// * JobSystem �Z�b�g����s������֐�
	Task m_task;

	// * �����p�ɏ����R���e�i�̃|�C���^��ێ����܂��B
	FunctionType m_funcType = FunctionType::None;
};