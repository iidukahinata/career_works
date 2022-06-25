/**
* @file    AsyncJobSystem.h
* @brief
*
* @date	   2022/06/23 2022�N�x����
*/
#pragma once


#include <queue>
#include <mutex>
#include "AsyncJob.h"
#include "SubSystem/Core/Common/Macro.h"

class AsyncJobSystem
{
	AsyncJobSystem() = default;
	COPY_PROHIBITED(AsyncJobSystem)
public:

	static AsyncJobSystem& Get() noexcept
	{
		static AsyncJobSystem instance;
		return instance;
	}

	~AsyncJobSystem();

	/**
	* �w��� thread ���g�p���ĕ��񏈗�������
	* @param threadCount [����] ���񏈗��Ŏg�p���� thred �����w�肷��B
	*/
	bool Initialize(int threadCount) noexcept;

	/**
	* ���񏈗��Ŏ��s����鏈���̒ǉ�
	* @param function [����] �ǉ���������֐����w��B
	*/
	void AddTask(AsyncJob* job) noexcept;

	/** CPU�ő�g�p�\�X���b�h����Ԃ� */
	int GetMaxThreadCount() const noexcept;

	/** �C���X�^���X�̉�����Ɏ��s����� */
	void Stop() noexcept;

private:

	/** �������ꂽ�e thread ���������� Task ���s���s���֐� */
	void ThreadLoop() noexcept;

private:

	// * ���񏈗����̏I�����Ǘ�����
	bool m_isRunning;

	// * �^�X�N���s����Ă��Ȃ� thread ����ێ�
	int m_numOfThreadsAvailable;

	// * ���񏈗��ŏ��Ɏ��s�����֐�
	std::queue<AsyncJob*> m_tasks;

	// * ���[�U�[�w�萔�� thread ����ύX���邽�߂ɉϒ��z��ŊǗ�
	std::vector<std::thread> m_threads;

	// * ���̃N���X���ł̔r����������p
	std::mutex m_mutex;

	std::condition_variable m_conditionVar;
};