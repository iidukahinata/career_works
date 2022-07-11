/**
* @file    MyGui.cpp
* @brief   gui管理クラス
*
* @date	   2022/06/25 2022年度初版
*/


#include "MyGui.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Renderer/D3D11/D3D11GrahicsDevice.h"
#include "ThirdParty/imgui/imgui_impl_dx11.h"
#include "ThirdParty/imgui/imgui_impl_win32.h"

void DrawFrameRate()
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(210, 50), ImGuiCond_Once);

	ImGui::Begin("Frame Rate");
	ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void MyGui::Init()
{
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(Window::Get().GetHandle());
	ImGui_ImplDX11_Init(D3D11GraphicsDevice::Get().GetDevice(), D3D11GraphicsDevice::Get().GetContext());

	ImGui::StyleColorsClassic();

	// fpsタイム描画
	AddWidget(DrawFrameRate);
}

void MyGui::Draw()
{
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
}

void MyGui::Exit()
{
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();
}

void MyGui::Clear()
{
	m_widgets.clear();
	m_widgets.shrink_to_fit();
}

void MyGui::AddWidget(Widget&& widget) noexcept
{
	m_widgets.emplace_back(widget);
}