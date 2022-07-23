/**
* @file    RenderCommandFance.h
* @brief
*
* @date	   2022/07/22 2022年度初版
*/
#pragma once


#include <wrl/client.h>

/**
* GameThread から RenderingCommand 追跡用クラス
*/
class RenderCommandFance
{
public:

	RenderCommandFance();
	~RenderCommandFance();

	/** Fance コマンドの追加 */
	void BegineFrame() noexcept;

	/** Fance コマンドが全て処理されるまで待機 */
	void WaitForSingle() const noexcept;

private:

	// * 追加されている Fance カウント
	std::atomic_uint32_t m_fanceValue;

	// * 待ちで使用される同期イベント
	HANDLE m_hEvent;
};