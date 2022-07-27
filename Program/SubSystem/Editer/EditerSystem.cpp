/**
* @file    MyGui.cpp
* @brief   gui管理クラス
*
* @date	   2022/07/26 2022年度初版
*/


#include "EditerSystem.h"
#include "Widget.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Renderer/D3D12/D3D12GrahicsDevice.h"
#include "ThirdParty/imgui/imgui_impl_dx12.h"
#include "ThirdParty/imgui/imgui_impl_win32.h"

void EditerSystem::Initialize() noexcept
{
	m_descriptHeap.Create(1, DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	ImGui::CreateContext();
	ImGui_ImplWin32_Init(Window::Get().GetHandle());
	ImGui_ImplDX12_Init(D3D12GraphicsDevice::Get().GetDevice(),
		1, DXGI_FORMAT_R8G8B8A8_UNORM,
		m_descriptHeap.Get(),
		m_descriptHeap.GetCPUDescriptorHandleForHeapStart(),
		m_descriptHeap.GetGPUDescriptorHandleForHeapStart());

	ImGui::StyleColorsClassic();
}

void EditerSystem::BegineFrame() noexcept
{
	if (!isRender)
	{
		return;
	}

	// start the dear ImGui frame
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	// draw user gui
	for (auto& widget : m_widgets)
	{
		widget->Draw();
	}

	isRender = false;
}

void EditerSystem::Render() noexcept
{
	if (isRender)
	{
		return;
	}

	// rendering
	ImGui::Render();
	m_descriptHeap.Set();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), D3D12GraphicsDevice::Get().GetCommandList());

	isRender = true;
}

void EditerSystem::Exit() noexcept
{
	m_widgets.clear();

	ImGui_ImplDX12_Shutdown();
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