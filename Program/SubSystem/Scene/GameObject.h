/**
* @file    GameObject.h
* @brief   �eGameObject�̒��ۃN���X
*
* @date	   2022/04/30 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include "Transform.h"

class IGameObject
{
public:

	virtual ~IGameObject() {}

	/**
	* �T�u�N���X�ŏ���������������������
	* Scene�o�^���ɌĂяo�����悤�ɐ݌v����Ă���
	* ���f�������\�[�X�ǂݍ��݂� Scene �� Init �����̎������@�Ɉˑ����邽�߁A
	* Awake �ŏ����Ă������Ƃ𐄏��B
	*/
	virtual void Awake() {}

	/**
	* �T�u�N���X�ŏ���������������������
	* �Ăяo���^�C�~���O�͏��� Scene �̎������@�ŕω�
	* ��{�I�ɑS�Ă� GameObject ����������Ă�����s�����B
	*/
	virtual void Init() {}

	/**
	* �T�u�N���X�ōX�V����������������
	* �Ăяo���^�C�~���O�͏��� Scene �̎������@�ŕω�
	*/
	virtual void Update() {}

	/**
	* �T�u�N���X�ŕ`�揈��������������
	* �Ăяo���^�C�~���O�͏��� Scene �̎������@�ŕω�
	*/
	virtual void Draw() {}

	int GetID() const noexcept;
	void SetID(int id) noexcept;

	/* Scene�N���X�Ō������Ŏg�p����� */
	virtual const char* GetName() { return nullptr; }

	Transform& GetTransform() noexcept;

	/** �x���Z�b�g�A�b�v */
	void SetScene(class IScene* scene) noexcept;

protected:

	// * Scene�N���X�ŒT�������Ɏg�p�����
	int m_id;

	Transform m_transform;

	class IScene* m_scene = nullptr;
};