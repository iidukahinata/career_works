/**
* @file    Stage.h
* @brief
*
* @date	   2022/06/09 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include "IMass.h"
#include "SubSystem/Resource/Resources/2DSprite/Sprite.h"

// 配列の要素指定時に使用するため、class 指定しない。
enum FloorType
{
	FLOOR,
	MESSAGE,
	PUTENEMY,
	NONE,
};

class Stage : public IGameObject
{
public:

	// IGameObject
	void Awake() override;
	void Init() override;
	void Draw() override;

	const char* GetName() override;

	bool SetMass(Math::Vector3i pos, IMass* data) noexcept;
	bool RemoveMass(IMass* mass) noexcept;

	IMass* GetMassData(Math::Vector3i pos) noexcept;
	FloorType GetMassType(Math::Vector3i pos) noexcept;
	int GetMassHight(Math::Vector3i pos) noexcept;

	bool LoadMapChip(int world, int stage) noexcept;
	bool SaveMapChip(int world, int stage) const noexcept;

	void CreatePlayer(Math::Vector3i pos) noexcept;
	void CreateEnemy(Math::Vector3i pos) noexcept;
	void CreateHuman(Math::Vector3i pos) noexcept;
	void CreateMessage(Math::Vector3i pos) noexcept;

	bool IsClear() const noexcept;

private:

	void ClearMap() noexcept;

private:

	std::vector<Sprite> m_massSprites;

	static const int MaxMapSize = 10;

	//* マス情報,　Y座標
	std::pair<FloorType, int> m_map[MaxMapSize][MaxMapSize] = { };
	IMass* m_mases[MaxMapSize][MaxMapSize] = { 0 };

	int m_humansCount = 0;
};