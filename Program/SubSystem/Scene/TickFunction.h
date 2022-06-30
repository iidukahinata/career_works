/**
* @file    TickFunction.h
* @brief
*
* @date	   2022/06/30 2022年度初版
*/
#pragma once


#include <stdint.h>

class TickFunction
{
public:

	virtual void Tick(double deltaTime) = 0;

	void RegisterToTickManager() noexcept;
	void UnRegisterFromTickManager() noexcept;

	bool IsRegistered() noexcept;

	void SetPriority(uint32_t priority) noexcept;
	uint32_t GetPriority() const { return m_priority; }

private:

	// * 更新順序優先度 0 に近い値が優先される。
	uint32_t m_priority = 128;
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