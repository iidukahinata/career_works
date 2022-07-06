/**
* @file		Job.h
* @brief
*
* @date		2022/07/06 2022�N�x����
*/
#pragma once


enum FunctionType
{
	Update,

	Render,

	None,
};

class Job
{
	friend class JobSystem;

	typedef Function<void(double)> Task;
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

	/** �X�V�������s�����߂ɂ́A��x���s���Ȃ���΂Ȃ�Ȃ��B*/
	void RegisterToJobSystem() noexcept;

	/** TickManager �ɓo�^�����ꍇ�A�Ăяo���K�v������܂��B*/
	void UnRegisterFromJobSystem() noexcept;

	bool IsRegistered() const noexcept;

private:

	bool m_isRegistered = false;

	// * JobSystem �Z�b�g����s������֐�
	Task m_task;

	// * �����p�ɏ����R���e�i�̃|�C���^��ێ����܂��B
	FunctionType m_funcType = FunctionType::None;
};