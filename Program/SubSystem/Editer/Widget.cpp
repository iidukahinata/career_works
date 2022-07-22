/**
* @file		Widget.cpp
* @brief
*
* @date		2022/07/19 2022îNìxèâî≈
*/


#include "Widget.h"
#include "EditerSystem.h"

Widget::Widget(Task&& task) noexcept
{
	SetFunction(std::forward<Task>(task));
}

Widget::~Widget()
{
	UnRegisterFromEditerSystem();
}

void Widget::Draw() noexcept
{
	m_task();
}

void Widget::SetFunction(Task&& task) noexcept
{
	m_task = std::forward<Task>(task);
}

void Widget::RegisterToEditerSystem() noexcept
{
	if (!IsRegistered())
	{
		m_isRegistered = true;
		EditerSystem::Get().RegisterWidget(this);
	}
}

void Widget::UnRegisterFromEditerSystem() noexcept
{
	if (IsRegistered())
	{
		m_isRegistered = false;
		EditerSystem::Get().RemoveWidget(this);
	}
}

bool Widget::IsRegistered() const noexcept
{
	return m_isRegistered;
}