/**
* @file    Stage.cpp
* @brief
*
* @date	   2022/06/02 2022�N�x����
* @author  �ђ˗z��
*/


#include "Stage.h"

void Stage::Awake()
{
	// ���_���C�A�E�g�쐬
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// MassType ��������΁A���̕��̃e�N�X�`������ǉ�����K�v������܂��B
	SpriteDesc spriteDescs[FloorType::NONE];
	spriteDescs[0].filePath = "assets/Dice/texture/GREEN_STONE.bin";
	spriteDescs[1].filePath = "assets/Dice/texture/RED_SCISSOR.bin";
	spriteDescs[2].filePath = "assets/Dice/texture/BLUE_PAPER.bin";

	// �w�肳��Ă��Ȃ��ꍇ�̌x�������B
	if (spriteDescs[FloorType::NONE - 1].filePath == nullptr)
	{
		LOG_ERROR("mass type �̑S�Ẵe�N�X�`�����w�肳��Ă��܂���B: Stage.cpp");
	}

	m_massSprites.resize(FloorType::NONE);
	for (int i = 0; i < m_massSprites.size(); ++i)
	{
		spriteDescs[i].layout = vertexDesc;
		spriteDescs[i].layoutSize = ARRAYSIZE(vertexDesc);

		// ���f���s��̃X�P�[���l�ő傫�������\��Ȃ̂� 1 ���w��B
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

			// Box �̉��ʂɃy���|���̒��S�_�����킹�邽�߂̒���
			float adjustmentValue = -0.75f * 0.5f;

			// Y �ʒu�� playerBox �Əd�Ȃ�`�悪�o�O�邱�Ƃ����邽�߁A0.001f �������Ă���B
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
	// �͈͊O�A�N�Z�X��h������
	if (pos.x < 0 && pos.z < 0)
		return false;

	// �͈͊O�A�N�Z�X��h������
	if (pos.x >= MaxMapSize && pos.z >= MaxMapSize)
		return false;

	// �n�ʂ��Ȃ����ɏ��Ȃ��悤�ɂ��邽��
	if (GetMassType(pos) == FloorType::NONE)
		return false;

	// �i��o��Ȃ��悤�ɂ��邽��
	if (GetMassHight(pos) >= pos.y)
		return false;

	m_mases[pos.x][pos.y] = data;

	return true;
}

bool Stage::LoadMapChip(int world, int stage) noexcept
{
	auto name = std::to_string(world) + "_" + std::to_string(stage);

	// ���X�e�[�W�Ƃ��Ĉ�ԉ��� 0 �Ŗ��߂����̂��쐬�B
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