/**
* @file    BackGraund.h
* @brief
*
* @date	   2022/06/03 2022îNìxèâî≈
* @author  î—íÀózëæ
*/
#pragma once


#include "SubSystem/Scene/GameObject.h"
#include "SubSystem/Resource/Resources/2DSprite/Sprite.h"

class PartternBackGraound
{
public:

	void Awake() noexcept;
	void Init(class Camera* camera) noexcept;
	void Update() noexcept;
	void Draw(UINT index) noexcept;

private:

	Transform m_transform;

	static const int patternSize = 6;
	Sprite m_sprites[patternSize];

	static const int maxCentorPosSize = 10;
	Math::Vector3 m_patternCentorPositions[maxCentorPosSize];

	Math::Vector3 m_velocity = Math::Vector3(-0.02f, 0.02f, 0.f);

	Math::Vector3 m_bottomPos;
};

class SelectBackGraund : public IGameObject
{
public:

	enum class AnimMode
	{
		ScreenIn,
		ScreenOut,
		None,
	};

	// IGameObject
	void Awake() override;
	void Init() override;
	void Update() override;
	void Draw() override;

private:

	void ScreenInAnimUpdate() noexcept;
	void ScreenOutAnimUpdate() noexcept;

private:

	Sprite m_backSprite;

	class GameMaster* m_master = nullptr;

	PartternBackGraound m_parttern;

	AnimMode m_animMode = AnimMode::ScreenIn;

	int m_nowSelectSceneIndex = 0;

	float m_speed = -0.075f;
};