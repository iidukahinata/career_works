/**
* @file    RenderingThread.h
* @brief
*
* @date	   2022/07/22 2022�N�x����
*/
#pragma once


#include "Thread.h"

enum RenderCommandType
{
	Execute,
	Flush,
};

class RenderCommandFance
{
public:

	//void BegineFrame() noexcept;
	//void Wait() noexcept;

private:

	RenderCommandType m_type;
};

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
		m_taskList.push(std::forward<Command>(task));
	}

	/** �ǉ��҂� TaskList ���� CommandList �� Command �̓���ւ����� */
	void ReceivingCommand() noexcept;

	/** �O�t���[���Œǉ����ꂽ�R�}���h�����s */
	void CommandProcess() noexcept;

private:

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