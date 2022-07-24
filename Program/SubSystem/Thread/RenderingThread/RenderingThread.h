/**
* @file    RenderingThread.h
* @brief
*
* @date	   2022/07/24 2022年度初版
*/
#pragma once


#include "../Thread.h"

/**
* RenderingThread で順次処理される CommandList と CommandList 追加待ち TaskList を管理
* データ競合阻止のため Command の追加時の MainThread でのアクセスブロックによる待ち時間の発生等の問題より二つのキューを用意し回避している。
* 
* @note
* 今現在の実装方法をやめ、RenderingResource などの操作関数を処理するスレッドと描画コマンド(IASet)などを処理するスレッドを
* 分けて実装する方法の方がよりスレッド間を分離し、より良い実装なのではないか。
*/
class RenderCommandList
{
	typedef std::function<void()> Command;
public:

	/** GameThread 側からの使用アクセスされる Task 追加関数 */
	static void AddTask(Command&& task) noexcept
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_taskList.push(std::forward<Command>(task));
	}

	/** 
	* GameThread が RenderingThread より早く動いてる場合、RenderCommand が増えすぎないように調整するために作成。
	* しかしこの方法は推奨せず、使用する場合はコマンドが実行されない場合を考慮する必要がある。
	* 
	* @note
	* この関数を頼らざるを得ない場合は他スレッドに処理を受託する方法を検討した方がよい。
	* より簡単な方法は Commandクラスを実装し、関数が消去を考慮するなどの設定を持たせ、考慮するもののみを消去を行うなどの方法がある。
	*/
	static void FlushCommand() noexcept
	{
		Queue<Command> clearData;

		std::unique_lock<std::mutex> lock(m_mutex);
		m_taskList.swap(clearData);
	}

	/** 追加待ち TaskList から CommandList へ Command の入れ替え処理 */
	void ReceivingCommand() noexcept;

	/** 前フレームで追加されたコマンドを実行 */
	void CommandProcess() noexcept;

private:

	// * command の swap 時の排他制御で使用
	static std::mutex m_mutex;

	// * RenderingThread で順次処理される CommandList
	static Queue<Command> m_commandList;

	// * CommandList 追加待ちの TaskList
	static Queue<Command> m_taskList;
};

/**
* 使用者側で RenderingCommand の追加を行うためのインターフェース関数。
*/
template<class Func>
void RegisterRenderCommand(Func&& task) noexcept
{
	RenderCommandList::AddTask(std::forward<Func>(task));
}

class RenderingThread : public IThread
{
	SUB_CLASS(RenderingThread)
public:

	/** RenderingThread の立ち上げ処理を行う。*/
	static void Start() noexcept;

	/** RenderingThread の終了処理を行う。*/
	static void Stop() noexcept;

	/**
	* GemaThread 開始時に呼び出される。
	* RenderingThread での開始処理のコマンドセットを行う。
	*/
	static void BegineFrame() noexcept;

	/**
	* GemaThread 終了時に呼び出される。
	* RenderingThread での終了処理のコマンドセットを行う。
	*/
	static void EndFrame() noexcept;

	/**
	* RenderingThread で処理されるコマンド処理が終了するまで待機する。
	* 主に、アプリケーション終了時などに使用する。
	*/
	static void WiatForRenderCommand() noexcept;

	void Run() override;

private:

	RenderCommandList m_renderCommandList;
};