/**
* @file    ThreadManager.h
* @brief
*
* @date	   2022/07/24 2022�N�x����
*/
#pragma once


#include "Thread.h"

/**
* IThread �N���X�͐���(�����ĂS��)�����h�����Ȃ��Ƒz�肵�Ď������Ă��邽�߁A
* Hash �l�̔����l�������݌v�ɂ������O�ύX�𐄏����Ă���B
*/
class ThreadManager
{
public:

	static ThreadManager& Get() noexcept
	{
		static ThreadManager instance;
		return instance;
	}

	/** �X���b�h���쐬���A�� Thread ��� Run�֐������s�B*/
	template<class T>
	void CreateThread() noexcept;

	/** �w��X���b�h�� Run�֐� ���I������܂őҋ@������B*/
	void QuitThread(StringView threadName) noexcept;

private:

	/** thread class ���\�b�h */
	void RegisterThread(IThread* ptr, const uint32_t hash) noexcept;
	void UnRegisterThread(const uint32_t hash) noexcept;

	/** async run job ���\�b�h */
	template<typename Func>
	void AddAsyncJob(const uint32_t hash, Func&& func) noexcept;
	void RemoveAsyncJob(const uint32_t hash) noexcept;

private:

	Map<uint32_t, UniquePtr<IThread>> m_threads;
	Map<uint32_t, AsyncJob> m_threadJob;
};

template<class T>
FORCEINLINE void ThreadManager::CreateThread() noexcept
{
	const uint32_t threadId = T::TypeData.Hash;
	T* newThread = NewObject<T>();

	RegisterThread(newThread, threadId);
	AddAsyncJob(threadId, [this, newThread]() { newThread->Run(); });

	// �ǉ����� Job �����s
	m_threadJob[threadId].RegisterToJobSystem();
}

template<typename Func>
FORCEINLINE void ThreadManager::AddAsyncJob(const uint32_t hash, Func&& func) noexcept
{
	ASSERT(!m_threadJob.contains(hash));
	m_threadJob.emplace(std::pair<uint32_t, AsyncJob>(hash, func));
}