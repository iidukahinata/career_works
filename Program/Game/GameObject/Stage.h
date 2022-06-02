/**
* @file    Stage.h
* @brief
*
* @date	   2022/06/02 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include "IMass.h"
#include "SubSystem/Resource/Resources/2DSprite/Sprite.h"

// �z��̗v�f�w�莞�Ɏg�p���邽�߁Aclass �w�肵�Ȃ��B
enum FloorType
{
	STONE,
	SCISSORS,
	PAPER,
	NONE,
};

class Stage : public IGameObject
{
public:

	// IGameObject
	void Awake() override;
	void Init() override;
	void Update() override;
	void Draw() override;

	const char* GetName() override;

	bool SetMass(Math::Vector3i pos, IMass* data) noexcept;

	IMass* GetMassData(Math::Vector3i pos) noexcept;
	FloorType GetMassType(Math::Vector3i pos) noexcept;
	int GetMassHight(Math::Vector3i pos) noexcept;

	bool LoadMapChip(int world, int stage) noexcept;
	bool SaveMapChip(int world, int stage) const noexcept;

private:

	void ClearMap() noexcept;

private:

	static const int MaxMapSize = 10;

	//* �}�X���,�@Y���W
	std::pair<FloorType, int> m_map[MaxMapSize][MaxMapSize];
	IMass* m_mases[MaxMapSize][MaxMapSize] = {};

	std::vector<Sprite> m_massSprites;
};