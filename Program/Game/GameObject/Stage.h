#pragma once


#include "IMass.h"
#include "SubSystem/Resource/Resources/2DSprite/Sprite.h"

enum MassType
{
	MASS_TYPE_STONE,
	MASS_TYPE_SCISSORS,
	MASS_TYPE_PAPER,
	MASS_TYPE_NONE,
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

	MassType GetMassType(int x, int y) noexcept;

private:

	void ClearMap() noexcept;
	void LoadMapChip() noexcept;

private:

	static const int MaxMapSize = 10;

	MassType m_map[MaxMapSize][MaxMapSize];

	std::vector<Sprite> m_massSprites;
};