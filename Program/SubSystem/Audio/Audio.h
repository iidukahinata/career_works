/**
* @file    Audio.h
* @brief
*
* @date	   2022/06/28 2022年度初版
*/
#pragma once


#include "SubSystem/Core/ISubsystem.h"

class AudioListener;

/**
* Audio抽象クラス
* このクラスではインターフェースのみを実装。
* 派生クラスで初期化等の関数を実装する。
*/
class Audio : public ISubsystem
{
	SUB_CLASS(Audio)
public:

	virtual bool Initialize() override { return true; }
	virtual void Shutdown() override {}

	/** 3D サウンドを使用する場合は必ず値をセットする必要があります。*/
	void SetAudioListener(AudioListener* listener) noexcept;

protected:

	class AudioListener* m_lisrener = nullptr;
};