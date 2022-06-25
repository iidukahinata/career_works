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
	float m_alpha;
	Math::Vector3 m_ambient;	//���F
	Math::Vector3 m_diffuse;	//�f�B�t���[�Y�F
	Math::Vector3 m_specular;	//�X�y�L�����F
	Math::Vector3 m_emissive;   //�G�~�b�V�u

	float m_specularPower;			//�X�y�L��������
	uint32_t indicesNum;			//�C���f�b�N�X��
};