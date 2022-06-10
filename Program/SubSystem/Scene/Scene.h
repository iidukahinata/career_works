/**
* @file    Scene.h
* @brief   �V�[�����ۃN���X
*
* @date	   2022/05/28 2022�N�x����
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
	* ���f�������\�[�X�ǂݍ��ݏ��������Q�[���I�u�W�F�N�g�̐��������������ƌ���������\��������B
	* �������AIO�����͈�莞�Ԃ�葁���Ȃ�Ȃ��̂� SetUp �҂����Ԃ����邱�Ƃł̒Z�k�̂�
	* ��F�O�̃V�[���Ŏg�p���Ă������\�[�X��ǂݍ��ށA�������\�[�X�̓ǂݍ��ݑ҂��𖳂����B
	*/
	virtual void Awake() {};

	/**
	* �T�u�N���X�ŏ����������������������� 
	* �V�[�����؂�ւ���Ă��珈������鏉�����֐��B
	*/
	virtual void Init();

	/** �T�u�N���X�ōX�V������������������ */
	virtual void Update();

	/** �T�u�N���X�ŕ`�掞���������������� */
	virtual void Draw();

	/** Scene �I�����̃T�u�N���X�ł̉������������ */
	virtual void Clear();

	virtual const char* GetName() = 0;

	/** GameObject function */
	template<class T>
	T* AddGameObject();
	void AddGameObject(IGameObject* gameObject);

	template<class T>
	T* GetGameObject(std::string_view name);
	IGameObject* GetGameObject(std::string_view name);

	void RemoveGameObject(IGameObject* gameObject);
	std::vector<std::unique_ptr<IGameObject>>& GetGameObjects() noexcept;

	/** �A�N�Z�X */
	Camera* GetMainCamera() const noexcept;
	LightMap* GetLightMap() noexcept;

	/** �x���Z�b�g�A�b�v */
	void SetSceneManager(class SceneManager* sceneManager) noexcept;
	class SceneManager* GetSceneManager() const noexcept;

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

template<class T>
inline T* IScene::AddGameObject()
{
	auto gameObject = new T;

	// �������Ԃ̒Z�k�̂��߂ɔz��ԍ���ID�Ƃ���
	gameObject->SetID(m_gameObjects.size());
	gameObject->SetScene(this);

	gameObject->Awake();

	m_gameObjects.emplace_back(gameObject);
	return gameObject;
}

template<class T>
inline T* IScene::GetGameObject(std::string_view name)
{
	for (auto& gameObject : m_gameObjects)
	{
		if (gameObject->GetName() == name.data())
		{
			return dynamic_cast<T*>(gameObject.get());
		}
	}
	return nullptr;
}