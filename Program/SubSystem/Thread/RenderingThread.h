/**
* @file    RenderingThread.h
* @brief
*
* @date	   2022/07/22 2022年度初版
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
* RenderingThread で順次処理される CommandList と CommandList 追加待ち TaskList を管理
* データ競合阻止のため Command の追加時の MainThread でのアクセスブロックによる待ち時間の発生等の問題より二つのキューを用意し回避している。
*/
class RenderCommandList
{
	typedef std::function<void()> Command;
public:

	/** GameThread 側からの使用アクセスされる Task 追加関数 */
	static void AddTask(Command&& task) noexcept
	{
		m_taskList.push(std::forward<Command>(task));
	}

	/** 追加待ち TaskList から CommandList へ Command の入れ替え処理 */
	void ReceivingCommand() noexcept;

	/** 前フレームで追加されたコマンドを実行 */
	void CommandProcess() noexcept;

private:

	// * RenderingThread で順次処理される CommandList
	static Queue<Command> m_commandList;

	// * CommandList 追加待ちの TaskList
	static Queue<Command> m_taskList;
};

/**
* 使用者側で RenderingCommand の追加を行うためのインターフェース関数。
* この関数を使用し、追加された Command は１フレーム遅れて実行される。
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