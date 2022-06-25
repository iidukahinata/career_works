/**
* @file		Job.h
* @brief
*
* @date		2022/06/23 2022�N�x����
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
	* JobSystem �Ŏ��s�����֐� function ��ݒ�
	* @note
	*  �����ɂ� double �^���󂯎��K�v������܂��B
	*/
	void SetFunction(Task&& task) noexcept;

	/* �����R���e�i�Ŏg�p�����֐��ł��B */
	void SetPointer(Pointer jobContainer) noexcept;
	Pointer GetPointer() const noexcept;
	void SetId(uint32_t id) noexcept;
	uint32_t GetId() const noexcept;

private:

	//* JobSystem �Z�b�g����s������֐�
	Task m_task;

	//* �����p�ɏ����R���e�i�̃|�C���^��ێ����܂��B
	Pointer m_jobContainer = nullptr;

	//* �R���e�i�ł̔z��̗v�f�ʒu��ێ����܂��B
	uint32_t m_id = -1;
};