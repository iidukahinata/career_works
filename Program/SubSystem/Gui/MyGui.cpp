/**
* @file    MyGui.cpp
* @brief   gui管理クラス
*
* @date	   2022/04/27 2022年度初版
* @author  飯塚陽太
*/


#include "MyGui.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Renderer/D3D11/D3D11GrahicsDevice.h"
#include "ThirdParty/imgui/imgui_impl_dx11.h"
#include "ThirdParty/imgui/imgui_impl_win32.h"

void MyGui::Init()
{
#ifdef _DEBUG
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(Window::Get().GetHandle());
	ImGui_ImplDX11_Init(D3D11GrahicsDevice::Get().GetDevice(), D3D11GrahicsDevice::Get().GetContext());

	ImGui::StyleColorsClassic();
#endif // _DEBUG
}

void MyGui::Draw()
{
#ifdef _DEBUG
	// start the dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// Run
	for (auto& widget : m_widgets)
	{
		widget();
	}

	// rendering
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif // _DEBUG
}

void MyGui::Exit()
{
#ifdef _DEBUG
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();
#endif // _DEBUG
}

void MyGui::Clear()
{
#ifdef _DEBUG
	m_widgets.clear();
	m_widgets.shrink_to_fit();
#endif // _DEBUG
}

void MyGui::AddWidget(Widget&& widget) noexcept
{
#ifdef _DEBUG
	m_widgets.emplace_back(widget);
#endif // _DEBUG
}