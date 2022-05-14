/**
* @file    ThreadPool.h
* @brief	���񏈗��N���X
*
* @date	   2022/05/14 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include <queue>
#include <mutex>
#include <functional>

class ThreadPool
{
private:

	ThreadPool() = default;
	ThreadPool(const ThreadPool&) = default;
	ThreadPool& operator=(const ThreadPool&) = default;

public:

	static ThreadPool& Get() noexcept
	{
		static ThreadPool instance;
		return instance;
	}

	~ThreadPool();

	/**
	* �w��� thread ���g�p���ĕ��񏈗�������
	* @param threadCount [����] ���񏈗��Ŏg�p���� thred �����w�肷��B
	*							0 �ȉ��̏ꍇ�͏�������Ȃ��B
	*							CPU���̃X���b�h�����傫���ꍇ����������Ȃ��B
	*/
	bool Init(int threadCount) noexcept;

	typedef std::function<void()> ThreadClosure;

	/**
	* ���񏈗��Ŏ��s����鏈���̒ǉ�
	* @param function [����] �ǉ���������֐����w��B
	*						 null�w���z�肵�Ă��Ȃ��B
	*/
	void AddTask(ThreadClosure&& function) noexcept;

	/**
	* �o�^���ꂽ�^�X�N���S�ďI������܂őҋ@ 
	* 
	* @note
	*  2022/04/24���_�ł�sleepfor���g�p�����҂����������Ă��Ȃ��B
	*/
	bool WaitForAllTasksToFinish() const noexcept;

	/** CPU�ő�g�p�\�X���b�h����Ԃ� */
	int GetMaxThreadCount() const noexcept;

private:

	/** �C���X�^���X�̉�����Ɏ��s����� */
	void Stop() noexcept;

	/** �������ꂽ�e thread ���������� Task ���s���s���֐� */
	void ThreadLoop() noexcept;

private:

	// * ���񏈗����̏I�����Ǘ�����
	bool m_isRunning;

	// * �^�X�N���s����Ă��Ȃ� thread ����ێ�
	int m_numOfThreadsAvailable;

	// * ���񏈗��ŏ��Ɏ��s�����֐�
	std::queue<ThreadClosure> m_tasks;

	// * ���[�U�[�w�萔�� thread ����ύX���邽�߂ɉϒ��z��ŊǗ�
	std::vector<std::thread> m_threads;

	// * ���̃N���X���ł̔r����������p
	std::mutex m_mutex;

	std::condition_variable m_conditionVar;
};