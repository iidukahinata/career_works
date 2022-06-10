/**
* @file    SceneManager.h
* @brief   �V�[���Ǘ��N���X
*
* @date	   2022/04/30 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include "Scene.h"
#include "SubSystem/ThreadPool/ThreadPool.h"

class SceneManager
{
public:

	void Update();
	void Draw();
	void Clear();

	/**
	* ���̊֐����ł� Scene �̐؂�ւ��͍s�킸�A���Ŏ��� Scene �ǂݍ��݂��J�n����B
	* �؂�ւ��́AUpdate ����Switing�Ƃ��� Scene �؂�ւ����s���B
	* ����� ChangeScene ���Ă΂��^�C�~���O�ŁA�������`��o���Ȃ��������肪���邽�߂��̂悤�ȏ����Ƃ���B
	*/
	template<class T>
	void ChangeScene();

private:

	/**
	* 2022/05/01 ���_�ł́A
	* �������̃��\�[�X�����œǂݍ��ގ��݂̂�z�肵�Ă���̂ŁA�֐����œǂݍ��ݑ҂����s���Ă���B
	* �������A���̋@�\�� ThreadPool ���g�p���Ă���ꍇ�A�����ɂ���Ă͖������[�v�ɓ���댯��������B
	*/
	void SceneSwitching();

private:

	enum class SceneState
	{
		Active,
		Stop,
		Change,
	};

	// * �V�[����Ԃ��Ǘ�
	SceneState m_sceneState = SceneState::Stop;

	// * ���݃V�[���I�u�W�F�N�g
	std::unique_ptr<IScene> m_currentScene;

	// * ���̃V�[���I�u�W�F�N�g
	std::unique_ptr<IScene> m_nextScene;
};

template<class T>
inline void SceneManager::ChangeScene()
{
	m_nextScene = std::make_unique<T>();
	m_nextScene->SetSceneManager(this);

	// �҂����������Ȃ��悤�A�V�[���ǂݍ��݂��I���������ɃV�[�����ւ��悤�ɂ��Ă���B
	ThreadPool::Get().AddTask([this] 
	{
		// ���݃V�[�����Ȃ����́A�o�b�N�ł̓ǂݍ��݂��s�v�̂��ߑ����ɑ҂��ɓ���B
		if (!m_currentScene)
		{
			m_sceneState = SceneState::Change;
		}

		m_nextScene->Awake();
		m_sceneState = SceneState::Change;
	});
}