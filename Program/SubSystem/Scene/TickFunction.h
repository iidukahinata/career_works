/**
* @file    TickFunction.h
* @brief
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


class TickFunction
{
public:

	virtual void Tick(double deltaTime) = 0;

	/** 更新処理を行うためには、一度実行しなければならない。*/
	void RegisterToTickManager() noexcept;

	/** TickManager に登録した場合、呼び出す必要があります。*/
	void UnRegisterFromTickManager() noexcept;

	/** 更新処理の待機、実行中なら true を返す。*/
	bool IsRegistered() const noexcept;

	void SetEnable(bool enable) noexcept;
	bool GetEnable() noexcept;

	void SetPriority(uint32_t priority) noexcept;
	uint32_t GetPriority() const noexcept;

private:

	// * 更新順序優先度 0 に近い値が優先される。
	uint32_t m_priority = 128;

	// * 更新処理の有効性を保持
	bool m_isEnabled = true;

	// * TickManager の登録されているかを保持
	bool m_isRegistered = false;
};

/**
* コンポーネント更新オブジェクト
*/
class TickComponentFunction : public TickFunction
{
public:

	class IComponent* m_component;

public:

	void Tick(double deltaTime);
};