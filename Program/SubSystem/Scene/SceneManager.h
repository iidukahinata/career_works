/**
* @file    SceneManager.h
* @brief   シーン管理クラス
*
* @date	   2022/04/30 2022年度初版
* @author  飯塚陽太
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
	* この関数内では Scene の切り替えは行わず、裏で次の Scene 読み込みを開始する。
	* 切り替えは、Update 内でSwitingとして Scene 切り替えを行う。
	* これは ChangeScene が呼ばれるタイミングで、正しく描画出来なかったり問題があるためこのような処理とする。
	*/
	template<class T>
	void ChangeScene();

private:

	/**
	* 2022/05/01 時点では、
	* 初期化のリソースを並列で読み込む事のみを想定しているので、関数内で読み込み待ちを行っている。
	* しかし、他の機能が ThreadPool を使用している場合、処理によっては無限ループに入る危険性がある。
	*/
	void SceneSwitching();

private:

	enum class SceneState
	{
		Active,
		Stop,
		Change,
	};

	// * シーン状態を管理
	SceneState m_sceneState = SceneState::Stop;

	// * 現在シーンオブジェクト
	std::unique_ptr<IScene> m_currentScene;

	// * 次のシーンオブジェクト
	std::unique_ptr<IScene> m_nextScene;
};

template<class T>
inline void SceneManager::ChangeScene()
{
	m_nextScene = std::make_unique<T>();
	m_nextScene->SetSceneManager(this);

	// 待ちが発生しないよう、シーン読み込みが終了した時にシーンが替わるようにしてある。
	ThreadPool::Get().AddTask([this] 
	{
		// 現在シーンがない時は、バックでの読み込みが不要のため即座に待ちに入る。
		if (!m_currentScene)
		{
			m_sceneState = SceneState::Change;
		}

		m_nextScene->Awake();
		m_sceneState = SceneState::Change;
	});
}