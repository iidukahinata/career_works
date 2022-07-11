/**
* @file    Light.h
* @brief
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


#include "../IComponent.h"

class Renderer;

enum class LightType
{
	DirectionalLight,
	PointLight,
	SpotLight,
	Max,
};

class Light : public IComponent
{
	SUB_CLASS(Light)
public:

	void Initialize() override;
	void Remove() override;

	void Active(bool active) override;

	void SetLightType(LightType lightType) noexcept;
	LightType GetLightType() const noexcept;

	void SetColor(const Math::Vector4& color) noexcept;
	const Math::Vector4& GetColor() const noexcept;

	void SetIntensity(float intensity) noexcept;
	float GetIntensity() const noexcept;

	void SetInfluenceRange(float influenceRange) noexcept;
	float GetInfluenceRange() const noexcept;

	void SetAngle(float angle) noexcept;
	float GetAngle() const noexcept;

private:

	void RegisterToLightMap() noexcept;
	void UnRegisterFromLightMap() noexcept;

private:

	LightType m_lightType;

	Math::Vector4 m_color;

	// * 光の強さ
	float m_intensity;

	// * 光の届く範囲
	float m_influenceRange;

	// * スポットライトの射出方向
	float m_angle;

	Renderer* m_renderer;
};