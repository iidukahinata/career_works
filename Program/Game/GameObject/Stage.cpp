

#include "Stage.h"

void Stage::Awake()
{
	// ���_���C�A�E�g�쐬
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// MassType ��������΁A���̕��̃e�N�X�`������ǉ�����K�v������܂��B
	SpriteDesc spriteDescs[MassType::MASS_TYPE_NONE];
	spriteDescs[0].filePath = "assets/Dice/texture/GREEN_STONE.bin";
	spriteDescs[1].filePath = "assets/Dice/texture/RED_SCISSOR.bin";
	spriteDescs[2].filePath = "assets/Dice/texture/BLUE_PAPER.bin";

	// �w�肳��Ă��Ȃ��ꍇ�̌x�������B
	if (spriteDescs[MassType::MASS_TYPE_NONE - 1].filePath == nullptr)
	{
		LOG_ERROR("mass type �̑S�Ẵe�N�X�`�����w�肳��Ă��܂���B: Stage.cpp");
	}

	m_massSprites.resize(MassType::MASS_TYPE_NONE);
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
	LoadMapChip();
}

void Stage::Update()
{
}

void Stage::Draw()
{
	for (int x = 0; x < MaxMapSize; ++x)
	{
		for (int y = 0; y < MaxMapSize; ++y)
		{
			if (m_map[x][y] == MASS_TYPE_NONE)
				continue;

			if (m_map[x][y] < 0)
				continue;

			if (m_map[x][y] >= m_massSprites.size())
				continue;

			m_transform.SetPosition(Math::Vector3(0.76f * x, -0.75f * 0.5f, 0.76f * y));
			m_massSprites[m_map[x][y]].Draw(m_transform.GetWorldMatrixXM());
		}
	}
}

const char* Stage::GetName()
{
	return "stage";
}

MassType Stage::GetMassType(int x, int y) noexcept
{
	return m_map[x][y];
}

void Stage::ClearMap() noexcept
{
	std::memset(m_map, (int)MassType::MASS_TYPE_NONE, sizeof(m_map));
}

void Stage::LoadMapChip() noexcept
{
	std::memset(m_map, 0, sizeof(m_map));
}