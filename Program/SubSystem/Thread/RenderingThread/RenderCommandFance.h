/**
* @file    RenderCommandFance.h
* @brief
*
* @date	   2022/07/24 2022年度初版
*/
#pragma once


#include <wrl/client.h>

/**
* GameThread から RenderingCommand 追跡用クラス
* BegineFrame を呼び出し追跡をスタートし、WaitForSingle、IsSingle 関数を使用して、状態を取得する。
*/
class RenderCommandFance
{
public:

	RenderCommandFance();
	~RenderCommandFance();

	/** Fance コマンドの追加 */
	void BegineFrame() noexcept;

	/** 
	* Fance コマンドが全て処理されるまで待機 
	* アプリケーションの終了処理など RenderingThread の終了合図が欲しい場面で使用
	*/
	void WaitForSingle() const noexcept;

	/**
	* Func コマンドが全て処理されたかを調べる 
	* GameThread での更新処理、解放処理での分岐などで使用する
	*/
	bool IsSingle() const noexcept;

private:

	// * 追加されている Fance カウント
	std::atomic_uint32_t m_fanceValue;

	// * 待ちで使用される同期イベント
	HANDLE m_hEvent;
};