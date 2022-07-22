/**
* @file    MyGui.cpp
* @brief   gui管理クラス
*
* @date	   2022/07/19 2022年度初版
*/


#include "EditerSystem.h"
#include "Widget.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Renderer/D3D11/D3D11GrahicsDevice.h"
#include "ThirdParty/imgui/imgui_impl_dx11.h"
#include "ThirdParty/imgui/imgui_impl_win32.h"

void EditerSystem::Initialize() noexcept
{
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(Window::Get().GetHandle());
	ImGui_ImplDX11_Init(D3D11GraphicsDevice::Get().GetDevice(), D3D11GraphicsDevice::Get().GetContext());

	ImGui::StyleColorsClassic();
}

void EditerSystem::Draw() noexcept
{
	// start the dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// draw user gui
	for (auto& widget : m_widgets)
	{
		widget->Draw();
	}

	// rendering
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void EditerSystem::Exit() noexcept
{
	m_widgets.clear();

	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();
}

void EditerSystem::RegisterWidget(Widget* widget) noexcept
{
	m_widgets.insert(widget);
}

void EditerSystem::RemoveWidget(Widget* widget) noexcept
{
	m_widgets.erase(widget);
}