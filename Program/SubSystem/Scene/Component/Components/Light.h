/**
* @file    Light.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include "../IComponent.h"

class Renderer;

class Light : public IComponent
{
	SUB_CLASS(Light)
public:

	enum class LightType
	{
		DirectionalLight,
		PointLight,
		SpotLight,
		Max,
	};

	void Initialize() override;
	void Remove() override;

	void Active(bool active) override;

	void SetLightType(LightType lightType);
	LightType GetLightType();

	void SetColor(const Math::Vector4& color);
	const Math::Vector4& GetColor();

	void SetIntensity(float intensity);
	float GetIntensity();

	void SetInfluenceRange(float influenceRange);
	float GetInfluenceRange();

	void SetAngle(float angle);
	float GetAngle();

private:

	void RegisterToLightMap() noexcept;
	void UnRegisterFromLightMap() noexcept;

private:

	LightType m_lightType;

	Math::Vector4 m_color;

	// * ���̋���
	float m_intensity;

	// * ���̓͂��͈�
	float m_influenceRange;

	// * �X�|�b�g���C�g�̎ˏo����
	float m_angle;

	Renderer* m_renderer;
};