/**
* @file    RenderingThread.h
* @brief
*
* @date	   2022/07/22 2022�N�x����
*/
#pragma once


#include "Thread.h"

/**
* RenderingThread �ŏ��������R�}���h�������I������܂őҋ@����B
* ��ɁA�A�v���P�[�V�����I�����ȂǂɎg�p�����B
*/
void FlushRenderCommand() noexcept;

/**
* RenderingThread �ŏ������������ CommandList �� CommandList �ǉ��҂� TaskList ���Ǘ�
* �f�[�^�����j�~�̂��� Command �̒ǉ����� MainThread �ł̃A�N�Z�X�u���b�N�ɂ��҂����Ԃ̔������̖�����̃L���[��p�ӂ�������Ă���B
*/
class RenderCommandList
{
	typedef std::function<void()> Command;
public:

	/** GameThread ������̎g�p�A�N�Z�X����� Task �ǉ��֐� */
	static void AddTask(Command&& task) noexcept
	{
		std::unique_lock lock(m_mutex);
		m_taskList.push(std::forward<Command>(task));
	}

	/** �ǉ��҂� TaskList ���� CommandList �� Command �̓���ւ����� */
	void ReceivingCommand() noexcept;

	/** �O�t���[���Œǉ����ꂽ�R�}���h�����s */
	void CommandProcess() noexcept;

private:

	// * command �� swap ���̔r������Ŏg�p
	static std::mutex m_mutex;

	// * RenderingThread �ŏ������������ CommandList
	static Queue<Command> m_commandList;

	// * CommandList �ǉ��҂��� TaskList
	static Queue<Command> m_taskList;
};

/**
* �g�p�ґ��� RenderingCommand �̒ǉ����s�����߂̃C���^�[�t�F�[�X�֐��B
* ���̊֐����g�p���A�ǉ����ꂽ Command �͂P�t���[���x��Ď��s�����B
*/
template<class Func>
void RegisterRenderCommand(Func&& task) noexcept
{
	RenderCommandList::AddTask(std::forward<Func>(task));
}

/**
* 
*/
class RenderingThread : public IThread
{
	SUB_CLASS(RenderingThread)
public:

	void Run() override;

private:

	RenderCommandList m_renderCommandList;
};