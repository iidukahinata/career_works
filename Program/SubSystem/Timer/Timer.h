/**
 * @file	Timer.h
 * @brief   フレーム管理クラス
 *
 * @date	2022/06/25 2022年度初版
 */
#pragma once


#include <chrono>
#include "SubSystem/Core/ISubsystem.h"

 /**
 * 可変フレームレートで制御出来るクラス
 */
class Timer : public ISubsystem
{
	SUB_CLASS(Timer)
public:

	bool Initialize() override;

	/**
	* 経過時間からフレームの状態を返す
	* mainLoop の先頭で使用されるように設計されている
	* @return true の場合は フレーム の更新合図
	* @note
	*   2022/04/24時点では制度が落ちるため、経過時間からsleep_forでの待ちを実装していない。
	*/
	bool ReachedNextFrame() noexcept;

	/** 中断されたアプリケーション再開時に時間調整のために使用される */
	void ResetMeasurement() noexcept;

	/**
	* 設定中の FPS 値 変更する時に使用
	* @param fps [入力] 変更後FPS値を指定。
	*					0 以下の値が指定された場合は処理されない
	*/
	void SetFPS(float fps) noexcept;

	/** 最後に ReachedNextFrame 関数で更新された時点の経過時間を返す */
	double GetDeltaTime() const noexcept;

private:

	// * 最新フレーム更新時間
	std::chrono::high_resolution_clock::time_point m_previousTime;

	// * フレーム経過時間(秒)
	double m_deltaTime;

	// * 設定中のFPS値を秒に変換した値
	double m_fpsTime;
};