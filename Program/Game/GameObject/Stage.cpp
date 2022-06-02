/**
* @file    Stage.cpp
* @brief
*
* @date	   2022/06/02 2022年度初版
* @author  飯塚陽太
*/


#include "Stage.h"

void Stage::Awake()
{
	// 頂点レイアウト作成
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// MassType が増えれば、その分のテクスチャ名を追加する必要があります。
	SpriteDesc spriteDescs[FloorType::NONE];
	spriteDescs[0].filePath = "assets/Dice/texture/GREEN_STONE.bin";
	spriteDescs[1].filePath = "assets/Dice/texture/RED_SCISSOR.bin";
	spriteDescs[2].filePath = "assets/Dice/texture/BLUE_PAPER.bin";

	// 指定されていない場合の警告処理。
	if (spriteDescs[FloorType::NONE - 1].filePath == nullptr)
	{
		LOG_ERROR("mass type の全てのテクスチャが指定されていません。: Stage.cpp");
	}

	m_massSprites.resize(FloorType::NONE);
	for (int i = 0; i < m_massSprites.size(); ++i)
	{
		spriteDescs[i].layout = vertexDesc;
		spriteDescs[i].layoutSize = ARRAYSIZE(vertexDesc);

		// モデル行列のスケール値で大きさ調整予定なので 1 を指定。
		spriteDescs[i].width = spriteDescs[i].height = 1.f;

		m_massSprites[i].Init(spriteDescs[i]);
	}
}

void Stage::Init()
{
	m_transform.SetScale(Math::Vector3(0.75f));
	m_transform.SetRotation(Math::Vector3(Math::ToRadian(90.f), 0.f, 0.f));

	ClearMap();
	LoadMapChip(1, 0);
}

void Stage::Update()
{
}

void Stage::Draw()
{
	for (int x = 0; x < MaxMapSize; ++x)
	{
		for (int z = 0; z < MaxMapSize; ++z)
		{
			if (m_map[x][z].first == FloorType::NONE)
				continue;

			if (m_map[x][z].first < 0)
				continue;

			if (m_map[x][z].first >= m_massSprites.size())
				continue;

			float posX = 0.75f * x;
			float posY = 0.75f * m_map[x][z].second;
			float posZ = 0.75f * z;

			// Box の下面にペラポリの中心点を合わせるための調整
			float adjustmentValue = -0.75f * 0.5f;

			// Y 位置は playerBox と重なり描画がバグることがあるため、0.001f 調整している。
			m_transform.SetPosition(Math::Vector3(posX, posY + adjustmentValue + 0.001f, posZ));
			m_massSprites[m_map[x][z].first].Draw(m_transform.GetWorldMatrixXM());
		}
	}
}

const char* Stage::GetName()
{
	return "stage";
}

IMass* Stage::GetMassData(Math::Vector3i pos) noexcept
{
	return m_mases[pos.x][pos.z];
}

FloorType Stage::GetMassType(Math::Vector3i pos) noexcept
{
	return m_map[pos.x][pos.z].first;
}

int Stage::GetMassHight(Math::Vector3i pos) noexcept
{
	return m_map[pos.x][pos.z].second;
}

bool Stage::SetMass(Math::Vector3i pos, IMass* data) noexcept
{
	// 範囲外アクセスを防ぐため
	if (pos.x < 0 && pos.z < 0)
		return false;

	// 範囲外アクセスを防ぐため
	if (pos.x >= MaxMapSize && pos.z >= MaxMapSize)
		return false;

	// 地面がない所に乗らないようにするため
	if (GetMassType(pos) == FloorType::NONE)
		return false;

	// 段を登らないようにするため
	if (GetMassHight(pos) >= pos.y)
		return false;

	m_mases[pos.x][pos.y] = data;

	return true;
}

bool Stage::LoadMapChip(int world, int stage) noexcept
{
	auto name = std::to_string(world) + "_" + std::to_string(stage);

	// 仮ステージとして一番下を 0 で埋めたものを作成。
	for (int x = 0; x < MaxMapSize; ++x)
	{
		for (int z = 0; z < MaxMapSize; ++z)
		{
			m_map[x][z] = std::pair<FloorType, int>(FloorType::STONE, 0);
		}
	}

	return true;
}

bool Stage::SaveMapChip(int world, int stage) const noexcept
{
	auto name = std::to_string(world) + "_" + std::to_string(stage);
	return true;
}

void Stage::ClearMap() noexcept
{
	for (int x = 0; x < MaxMapSize; ++x)
	{
		for (int z = 0; z < MaxMapSize; ++z)
		{
			m_map[x][z] = std::pair<FloorType, int>(FloorType::NONE, 0);
		}
	}
}