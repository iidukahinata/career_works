/**
* @file	   Renderer.h
* @brief
*
* @date	   2022/05/11 2022年度初版
* @author  飯塚陽太
*/


#include "Renderer.h"
#include "SubSystem/Renderer/D3D11/D3D11GrahicsDevice.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Gui/MyGui.h"
#include "ThirdParty/imgui/imgui.h"

void DrawFrameRate()
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(210, 50), ImGuiCond_Once);

	ImGui::Begin("Frame Rate");
	ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void Renderer::Init()
{
	D3D11GrahicsDevice::Get().Init();

	TransformCBuffer::Get().Init();

	MyGui::Get().Init();

	// fpsタイム描画
	MyGui::Get().AddWidget(DrawFrameRate);
}

void Renderer::BeginFream()
{
	D3D11GrahicsDevice::Get().Clear(Math::Vector4(0.f, 0.f, 0.f, 1.f));
}

void Renderer::EndFream()
{
	MyGui::Get().Draw();

	D3D11GrahicsDevice::Get().Present();
}

void Renderer::Exit()
{
	MyGui::Get().Exit();
}