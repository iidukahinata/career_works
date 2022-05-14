/**
* @file    Scene.h
* @brief   �V�[�����ۃN���X
*
* @date	   2022/05/06 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include <memory>
#include "GameObject.h"
#include "SubSystem/Renderer/Camera/Camera.h"
#include "SubSystem/Renderer/Drawings/Light/LightMap.h"

class IScene
{
public:

	virtual ~IScene() {}

	/**
	* �T�u�N���X�Ń��[�h������������������ 
	* ���̊֐����I�������^�C�~���O�ŃV�[�����؂�ւ��B
	* ���f�����̃��\�[�X�ǂݍ��ݏ����������ƌ���������\��������B
	* ��F�O�̃V�[���Ŏg�p���Ă������\�[�X��ǂݍ��ށA�������\�[�X�̓ǂݍ��ݑ҂��𖳂����B
	*/
	virtual void Awake() {};

	/**
	* �T�u�N���X�ŏ����������������������� 
	* �V�[�����؂�ւ���Ă��珈������鏉�����֐��B
	*/
	virtual void Init() {};

	/** �T�u�N���X�ōX�V������������������ */
	virtual void Update();

	/** �T�u�N���X�ŕ`�掞���������������� */
	virtual void Draw();

	/** Scene �I�����̃T�u�N���X�ł̉������������ */
	virtual void Clear();

	/** GameObject function */
	void AddGameObject(IGameObject* gameObject);
	IGameObject* GetGameObject(std::string_view name);
	void RemoveGameObject(int id);
	std::vector<std::unique_ptr<IGameObject>>& GetGameObjects() noexcept;

	/** �A�N�Z�X */
	Camera* GetMainCamera() const noexcept;
	LightMap* GetLightMap() noexcept;

	/** �x���Z�b�g�A�b�v */
	void SetSceneManager(class SceneManager* sceneManager) noexcept;

protected:

	// * �V�[�����I�u�W�F�N�g�z��
	std::vector<std::unique_ptr<IGameObject>> m_gameObjects;

	// * �T�u�J�����͔h����Ń��[�U�[�Ɋg�����Ă��炤
	std::unique_ptr<Camera> m_mainCamera;

	// * �V�[�����̃��C�g�Ǘ��N���X
	LightMap m_lightMap;

	DirectionalLight m_directionalLight;
	std::vector<PointLight> m_pointLights;
	std::vector<SpotLight> m_spotLights;

	class SceneManager* m_sceneManager = nullptr;
};