/**
* @file    RenderCommandFance.cpp
* @brief
*
* @date	   2022/07/22 2022îNìxèâî≈
*/


#include "RenderCommandFance.h"
#include "../RenderingThread.h"

RenderCommandFance::RenderCommandFance()
{
	m_hEvent = CreateEvent(nullptr, true, false, "Render");
	ASSERT(m_hEvent);
}

RenderCommandFance::~RenderCommandFance()
{
	CloseHandle(m_hEvent);
}

void RenderCommandFance::BegineFrame() noexcept
{
	++m_fanceValue;

	RegisterRenderCommand([this] {
		SetEvent(m_hEvent);
		--m_fanceValue;
	});
}

void RenderCommandFance::WaitForSingle() const noexcept
{
	while (0 < m_fanceValue)
	{
		if (WaitForSingleObject(m_hEvent, INFINITE) == WAIT_OBJECT_0)
		{
			ResetEvent(m_hEvent);
		}
	}
}