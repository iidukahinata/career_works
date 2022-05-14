/**
* @file    Material.h
* @brief
*
* @date	   2022/04/25 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include "SubSystem/Math/MathCore.h"

/**
* 2022/04/25 ���_�ł͎g�p����Ă��Ȃ����A����Ǝ��}�e���A���f�[�^�Ƃ��Ďg�p�\��B
* �܂����̎��̓}�e���A���Ńe�N�X�`���f�[�^���g�p����\��B
*/
struct Material
{
	float m_Alpha;
	Math::Vector3 m_Ambient;	//���F
	Math::Vector3 m_Diffuse;	//�f�B�t���[�Y�F
	Math::Vector3 m_Specular;	//�X�y�L�����F
	Math::Vector3 m_emissive;   //�G�~�b�V�u

	float m_specularPower;			//�X�y�L��������
	uint32_t indicesNum;			//�C���f�b�N�X��
};