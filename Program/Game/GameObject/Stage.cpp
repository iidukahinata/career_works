/**
* @file    Stage.cpp
* @brief
*
* @date	   2022/06/03 2022年度初版
* @author  飯塚陽太
*/


#include "Stage.h"
#include "Player.h"
#include "Human.h"
#include "Message.h"
#include "SubSystem/Scene/Scene.h"
#include "SubSystem/IOStream/FileStream.h"

#include "GameMaster.h"

void Stage::Awake()
{
	// 頂点レイアウト作成
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// MassType が増えれば、その分のテクスチャ名を追加する必要があります。
	SpriteDesc spriteDescs[FloorType::NONE];
	spriteDescs[0].filePath = "assets/Imqube/Floor/Floor.jpg";
	spriteDescs[1].filePath = "assets/Imqube/Floor/Hint.jpg";
	spriteDescs[2].filePath = "assets/Imqube/Floor/putEnemy.jpg";

	// 指定されていない場合の警告処理。
	if (spriteDescs[FloorType::NONE - 1].filePath.empty())
	{
		LOG_ERROR("mass type の全てのテクスチャが指定されていません。: Stage.cpp");
	}

	m_massSprites.resize(FloorType::NONE);
	for (int i = 0; i < m_massSprites.size(); ++i)
	{
		spriteDescs[i].layout = vertexDesc;
		spriteDescs[i].layoutSize = ARRAYSIZE(vertexDesc);

		m_massSprites[i].Init(spriteDescs[i]);
	}
}

void Stage::Init()
{
	m_transform.SetScale(Math::Vector3(0.75f));
	m_transform.SetRotation(Math::Vector3(Math::ToRadian(90.f), 0.f, 0.f));

	auto master = dynamic_cast<GameMaster*>(m_scene->GetGameObject("GameMaster"));

	ClearMap();
	LoadMapChip(master->LoadWorldNum(), master->LoadStageNum());
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
	// 範囲外アクセスを防ぐため
	if (pos.x < 0 || pos.z < 0)
		return nullptr;

	// 範囲外アクセスを防ぐため
	if (pos.x >= MaxMapSize || pos.z >= MaxMapSize)
		return nullptr;

	return m_mases[pos.x][pos.z];
}

FloorType Stage::GetMassType(Math::Vector3i pos) noexcept
{
	// 範囲外アクセスを防ぐため
	if (pos.x < 0 || pos.z < 0)
		return FloorType::NONE;

	// 範囲外アクセスを防ぐため
	if (pos.x >= MaxMapSize || pos.z >= MaxMapSize)
		return FloorType::NONE;

	return m_map[pos.x][pos.z].first;
}

int Stage::GetMassHight(Math::Vector3i pos) noexcept
{
	// 範囲外アクセスを防ぐため
	if (pos.x < 0 || pos.z < 0)
		return FloorType::NONE;

	// 範囲外アクセスを防ぐため
	if (pos.x >= MaxMapSize || pos.z >= MaxMapSize)
		return FloorType::NONE;

	return m_map[pos.x][pos.z].second;
}

bool Stage::SetMass(Math::Vector3i pos, IMass* data) noexcept
{
	// 範囲外アクセスを防ぐため
	if (pos.x < 0 || pos.z < 0)
		return false;

	// 範囲外アクセスを防ぐため
	if (pos.x >= MaxMapSize || pos.z >= MaxMapSize)
		return false;

	// 地面がない所に乗らないようにするため
	if (GetMassType(pos) == FloorType::NONE)
		return false;

	// 段を登らないようにするため
	if (GetMassHight(pos) < pos.y)
		return false;

	if (data)
	{
		data->SetMassPos(Math::Vector3i(pos.x, pos.y, pos.z));
	}

	m_mases[pos.x][pos.z] = data;

	return true;
}

bool Stage::RemoveMass(IMass* mass) noexcept
{
	if (mass == nullptr)
		return false;

	auto pos = mass->GetMassPos();

	// 範囲外アクセスを防ぐため
	if (pos.x < 0 || pos.z < 0)
		return false;

	// 範囲外アクセスを防ぐため
	if (pos.x >= MaxMapSize || pos.z >= MaxMapSize)
		return false;

	if (m_mases[pos.x][pos.z] == mass)
	{
		m_mases[pos.x][pos.z] = nullptr;
		return true;
	}
	return false;
}

bool Stage::LoadMapChip(int world, int stage) noexcept
{
	auto name = "assets/Imqube/Stage/" + std::to_string(world) + "_" + std::to_string(stage) + ".bin";

	FileStream file;
	if (!file.Load(name, OpenMode::Read_Mode))
	{
		return false;
	}
	
	std::vector<std::pair<FloorType, int>> m_mapMeta;
	file.Read(&m_mapMeta);
	std::memcpy(m_map, m_mapMeta.data(), sizeof(m_map));
	
	std::vector<std::pair<IMass::MassType, Math::Vector3i>> m_massMeta;
	file.Read(&m_massMeta);
	
	for (int i = 0; i < m_massMeta.size(); ++i)
	{
		switch (m_massMeta[i].first)
		{
		case IMass::MassType::PLAYER: CreatePlayer(m_massMeta[i].second); break;
		case IMass::MassType::ENEMY: CreateEnemy(m_massMeta[i].second);break;
		case IMass::MassType::HUMAN: CreateHuman(m_massMeta[i].second);break;
		case IMass::MassType::MESSEGE: CreateMessage(m_massMeta[i].second); break;
		default: break;
		}
	}
	return true;
}

bool Stage::SaveMapChip(int world, int stage) const noexcept
{
	auto name = "assets/Imqube/Stage/" + std::to_string(world) + "_" + std::to_string(stage) + ".bin";

	FileStream file;
	if (!file.CreateFileAndLoad(name, OpenMode::Write_Mode))
	{
		return false;
	}

	// 書き込みしやすいように一次元配列データにしている。
	std::vector<std::pair<FloorType, int>> m_mapMeta(MaxMapSize * MaxMapSize);
	std::memcpy(m_mapMeta.data(), m_map, sizeof(m_map));
	file.Write(m_mapMeta);

	// MassType : Position 情報を同じく一次元配列データにしている。
	std::vector<std::pair<IMass::MassType, Math::Vector3i>> m_massMeta;
	for (int x = 0; x < MaxMapSize; ++x)
	{
		for (int z = 0; z < MaxMapSize; ++z)
		{
			if (m_mases[x][z])
			{
				m_massMeta.emplace_back(m_mases[x][z]->GetType(), m_mases[x][z]->GetMassPos());
			}
		}
	}
	file.Write(m_massMeta);

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

void Stage::CreatePlayer(Math::Vector3i pos) noexcept
{
	Player* mass = new Player();
	SetMass(pos, mass);
	m_scene->AddGameObject(mass);
}

void Stage::CreateEnemy(Math::Vector3i pos) noexcept
{
	//Enemy* mass = new Enemy();
	//SetMass(pos, mass);
	//m_scene->AddGameObject(mass);
}

void Stage::CreateHuman(Math::Vector3i pos) noexcept
{
	Human* mass = new Human();
	SetMass(pos, mass);
	m_scene->AddGameObject(mass);

	++m_humansCount;
}

void Stage::CreateMessage(Math::Vector3i pos) noexcept
{
	m_map[pos.x][pos.z] = std::pair<FloorType, int>(FloorType::MESSAGE, pos.y);

	Message* mass = new Message();
	SetMass(pos, mass);
	m_scene->AddGameObject(mass);
	mass->MessegeSpriteInit(0);
}