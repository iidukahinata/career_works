/**
* @file    Thread.h
* @brief
*
* @date	   2022/07/24 2022�N�x����
*/
#pragma once


class IThread
{
	SUPER_CLASS(IThread)
	COPY_PROHIBITED(IThread)
public:

	IThread() = default;
	~IThread() {};

	virtual void Run() = 0;

	/** Run �֐��� Loop �������I�������邽�߂Ɏ��� */
	void RequestQuit() noexcept;

	bool IsRequestQuit() const noexcept;

private:

	// * �h���� Run �֐����� Loop �������L�q�����ۂɎg�p���AMainThread�Ƃ̘A�g���Ƃ�(��ɏI����)
	std::atomic_bool m_isRequestQuit = false;
};