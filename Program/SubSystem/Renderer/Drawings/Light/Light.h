/**
* @file	   Light.h
* @brief	Lightクラス群
*
* @date	   2022/04/22 2022年度初版
* @author  飯塚陽太
* @note
*						   	Light
*						   	 ↓
*		   ---------------------------------------
*	      ↓	                 ↓                  ↓
*	DirectionalLight	  PointLight		  SpotLight
*/
#pragma once


#include "SubSystem/Math/MathCore.h"

/*
* @note
*	各ライトの抽象クラス
*   各Lightごとで使用するパラメータが違うため、このクラスではライトパラメータを持たない。
* 　代わりに派生先で使用する各パラメータを返す関数を用意。
* 　派生先で用意した関数を拡張する。
*/
class Light
{
public:

	enum class LightType
	{
		DirectionalLight,
		PointLight,
		SpotLight,
		Max,
	};

	virtual ~Light() {};

	void Init(class LightMap* lightMap) 
	{
		m_lightMap = lightMap;
		Do_Init();
	}

	virtual void Do_Init() = 0;

	virtual LightType GetLightType()
	{
		return LightType::Max;
	}

	virtual void SetPosition(const Math::Vector4& position)
	{
	}

	virtual const Math::Vector4& GetPosition()
	{
		return Math::Vector4();
	}

	virtual void SetDirection(const Math::Vector4& direction)
	{
	}

	virtual const Math::Vector4& GetDirection()
	{
		return Math::Vector4();
	}

	virtual void SetColor(const Math::Vector4& color)
	{
	}

	virtual const Math::Vector4& GetColor()
	{
		return Math::Vector4();
	}

	virtual void SetInfluenceRange(const float& influenceRange)
	{
	}

	virtual const float& GetInfluenceRange()
	{
		return 0;
	}

	virtual void SetAngle(const float& angle)
	{
	}

	virtual const float& GetAngle()
	{
		return 0;
	}

	virtual void SetIntensity(const float& intensity)
	{
	}

	virtual const float& GetIntensity()
	{
		return 0;
	}

	void SetEnable(bool enable)
	{
		m_enable = enable;
	}

	bool GetEnable() 
	{
		return m_enable;
	}

protected:

	// * このパラメータがtrueの時にSceneで使用される
	bool m_enable = true;

	// * このクラスにLigthを登録することで、Sceneで使用される
	class LightMap* m_lightMap = nullptr;
};


class DirectionalLight : public Light
{
public:

	~DirectionalLight();

	void Do_Init() override;

	Light::LightType GetLightType() override;

	const Math::Vector4& GetDirection() override;
	void SetDirection(const Math::Vector4& direction) override;

	const Math::Vector4& GetColor() override;
	void SetColor(const Math::Vector4& color) override;

	const float& GetIntensity() override;
	void SetIntensity(const float& intensity) override;

private:

	Math::Vector4 m_direction;

	Math::Vector4 m_color;

	// * 光の強さ
	float m_intensity;
};


class PointLight : public Light
{
public:

	~PointLight();

	void Do_Init() override;

	Light::LightType GetLightType() override;

	const Math::Vector4& GetPosition() override;
	void SetPosition(const Math::Vector4& position) override;

	const Math::Vector4& GetColor() override;
	void SetColor(const Math::Vector4& color) override;

	const float& GetInfluenceRange() override;
	void SetInfluenceRange(const float& influenceRange);

	const float& GetIntensity() override;
	void SetIntensity(const float& intensity) override;

private:

	Math::Vector4 m_position;

	Math::Vector4 m_color;

	// * 光の届く範囲
	float m_influenceRange;

	// * 光の強さ
	float m_intensity;
};


class SpotLight : public Light
{
public:

	~SpotLight();

	void Do_Init() override;

	Light::LightType GetLightType() override;

	const Math::Vector4& GetPosition() override;
	void SetPosition(const Math::Vector4& position) override;

	const Math::Vector4& GetDirection() override;
	void SetDirection(const Math::Vector4& direction) override;

	const Math::Vector4& GetColor() override;
	void SetColor(const Math::Vector4& color) override;

	const float& GetInfluenceRange() override;
	void SetInfluenceRange(const float& influenceRange);

	const float& GetAngle() override;
	void SetAngle(const float& angle) override;

	const float& GetIntensity() override;
	void SetIntensity(const float& intensity) override;

public:

	Math::Vector4 m_position;

	Math::Vector4 m_direction;

	Math::Vector4 m_color;

	// * 光の届く範囲
	float m_influenceRange;

	// * スポットライトの射出方向
	float m_angle;

	// * 光の強さ
	float m_intensity;
};