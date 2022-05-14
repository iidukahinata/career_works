/**
* @file	   Light.h
* @brief	Light�N���X�Q
*
* @date	   2022/04/22 2022�N�x����
* @author  �ђ˗z��
* @note
*						   	Light
*						   	 ��
*		   ---------------------------------------
*	      ��	                 ��                  ��
*	DirectionalLight	  PointLight		  SpotLight
*/
#pragma once


#include "SubSystem/Math/MathCore.h"

/*
* @note
*	�e���C�g�̒��ۃN���X
*   �eLight���ƂŎg�p����p�����[�^���Ⴄ���߁A���̃N���X�ł̓��C�g�p�����[�^�������Ȃ��B
* �@����ɔh����Ŏg�p����e�p�����[�^��Ԃ��֐���p�ӁB
* �@�h����ŗp�ӂ����֐����g������B
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

	// * ���̃p�����[�^��true�̎���Scene�Ŏg�p�����
	bool m_enable = true;

	// * ���̃N���X��Ligth��o�^���邱�ƂŁAScene�Ŏg�p�����
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

	// * ���̋���
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

	// * ���̓͂��͈�
	float m_influenceRange;

	// * ���̋���
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

	// * ���̓͂��͈�
	float m_influenceRange;

	// * �X�|�b�g���C�g�̎ˏo����
	float m_angle;

	// * ���̋���
	float m_intensity;
};