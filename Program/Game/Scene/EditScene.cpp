#include "EditScene.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Input/Input.h"
#include "../GameObject/Player.h"
#include "../GameObject/Road.h"
#include "SubSystem/Renderer/Drawings/Effect/PostEffect/Blur.h"
#include "SubSystem/Renderer/Drawings/Effect/PostEffect/Bloom.h"
#include "SubSystem/Renderer/Drawings/Effect/PostEffect/Monotone.h"
#include "SubSystem/Renderer/Drawings/Effect/PostEffect/DepthOfField.h"

#include "ThirdParty/imgui/imgui.h"
#include "SubSystem/Gui/MyGui.h"

Math::Vector4 dir1 = { 0.5f, -0.5f, -1.f, 0.f };

Player* player = nullptr;

static const int BUFFER_TEXT_DEFAULT = 255;
static void SetCharArray(char* array, const std::string& value)
{
	if (value.length() > BUFFER_TEXT_DEFAULT)
		return;

	memset(&array[0], 0, BUFFER_TEXT_DEFAULT * sizeof(array[0]));
	copy(value.begin(), value.end(), array);
}

void DrawPlayer()
{
	ImGui::SetNextWindowPos(ImVec2(1000, 10), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(220, 100), ImGuiCond_Once);
	ImGui::Begin("Player");

	// position
	float pos[3] = { player->GetTransform().GetPosition().x, player->GetTransform().GetPosition().y, player->GetTransform().GetPosition().z };
	ImGui::InputFloat3(" pos ", pos);
	player->GetTransform().SetPosition(Math::Vector3(pos[0], pos[1], pos[2]));

	ImGui::End();
}

void EditScene::Init()
{
	m_lightMap.Init();
	postprocessing.Init();
	skyBox.Init("assets/SkyBox/skybox.dds");

	m_mainCamera = std::make_unique<Camera>();
	m_mainCamera->GetTransform().LockAt(Math::Vector3::Zero);

	player = new Player();
	player->GetTransform().SetRotation(Math::Vector3(0.f, 10.f, 0.f));
	AddGameObject(player);

	m_directionalLight.Init(&m_lightMap);
	m_directionalLight.SetDirection(dir1);
	m_directionalLight.SetColor({ 1.f });
	m_directionalLight.SetIntensity(1);
	m_lightMap.SetAmbient({ 0.4f });

	MyGui::Get().AddWidget(DrawPlayer);
}

void EditScene::Update()
{
	IScene::Update();

	m_mainCamera->Update(Math::Vector3::Zero, Math::Vector3::Zero);

	postprocessing.Update();

	m_lightMap.Update(m_mainCamera->GetTransform().GetWoldPosition());
}

void EditScene::Draw()
{
	TransformCBuffer::Get().SetProjection(m_mainCamera->GetProjectionMatrixXM());
	TransformCBuffer::Get().SetView(m_mainCamera->GetViewMatrixXM());

	skyBox.Draw(m_mainCamera->GetTransform().GetWoldPosition());

	IScene::Draw();

	Transform camera2D;
	camera2D.SetPosition(Math::Vector3(0.f, 0.f, -1.f));
	TransformCBuffer::Get().SetView(DirectX::XMMatrixInverse(nullptr, camera2D.GetWorldMatrixXM()));
	TransformCBuffer::Get().SetProjection(m_mainCamera->GetOrthographicMatrixXM());

	postprocessing.Draw();
}