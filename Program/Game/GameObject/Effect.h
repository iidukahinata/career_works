/**
* @file    Effect.h
* @brief
*
* @date	   2022/06/08 2022îNìxèâî≈
* @author  î—íÀózëæ
*/
#pragma once


#include "SubSystem/Scene/GameObject.h"
#include "SubSystem/Resource/Resources/2DSprite/Sprite.h"
#include "SubSystem/Renderer/D3D11/D3D11ConstantBuffer.h"

class Effect : public IGameObject
{
public:

	// IGameObject
	void Init() override;
	void Update() override;
	void Draw() override;

private:

	void SetColor(const Math::Vector4& color) noexcept;

	struct EffectData
	{
		Transform m_transform;

		Math::Vector4 m_color = Math::Vector4(1.f, 1.f, 1.f, 0.5f);
		int m_timeCount = 0;
		int m_maxTmeCount = 180;
		Math::Vector3 m_direction = Math::Vector3(0);
	};

	void EffectDataUpdate(EffectData* data, int index) noexcept;

	EffectData CreateEffectData() const noexcept;

private:

	struct ConstantBufferColor
	{
		Math::Vector4 m_color;
	};

	D3D11ConstantBuffer<ConstantBufferColor> m_constantBuffer;

	Sprite m_sprite;

	std::vector<EffectData> m_effects;
};