/**
* @file    Stage.h
* @brief
*
* @date	   2022/06/02 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include "IMass.h"
#include "SubSystem/Resource/Resources/2DSprite/Sprite.h"

// 配列の要素指定時に使用するため、class 指定しない。
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

	//* マス情報,　Y座標
	std::pair<FloorType, int> m_map[MaxMapSize][MaxMapSize];
	IMass* m_mases[MaxMapSize][MaxMapSize] = {};

	std::vector<Sprite> m_massSprites;
};