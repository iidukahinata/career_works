#include "EditScene.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Input/Input.h"

#include "ThirdParty/imgui/imgui.h"
#include "SubSystem/Gui/MyGui.h"

void DrawPlayer()
{
	ImGui::SetNextWindowPos(ImVec2(1000, 10), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(220, 100), ImGuiCond_Once);
	ImGui::Begin("Player");

	// position
	//float pos[3] = { player->GetTransform().GetPosition().x, player->GetTransform().GetPosition().y, player->GetTransform().GetPosition().z };
	//ImGui::InputFloat3(" pos ", pos);
	//player->GetTransform().SetPosition(Math::Vector3(pos[0], pos[1], pos[2]));

	ImGui::End();
}

void EditScene::Init()
{
	MyGui::Get().AddWidget(DrawPlayer);
}

void EditScene::Update()
{
	IScene::Update();

	m_mainCamera->Update();

	m_lightMap.Update(m_mainCamera->GetTransform().GetWoldPosition());
}

void EditScene::Draw()
{
	TransformCBuffer::Get().SetProjection(m_mainCamera->GetProjectionMatrixXM());
	TransformCBuffer::Get().SetView(m_mainCamera->GetViewMatrixXM());

	IScene::Draw();
}